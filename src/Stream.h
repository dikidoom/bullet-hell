#pragma once

// composition order:
// INPUTS:
// dt -------------------------->|
// sequence -> composition -> time -> count -> bullet -> angle
//                                                    -> speed
//                                    |<------ Bullet*
// |<-------------------------------- BulletArray*
// OUTPUTS:

// ???????? how to implement ????????
// carousel (in1, in2, ..., inn ): each next() switches b/w in1,
// in2, ..., inn, in1, in2, ...)

// how about: all streams return the same type?
// e.g. bulletarray?
// and take the same deltatime-argument (and just don't use it?)
// then we can mix and match freely?

// can Take/Count be called MultiPoll instead?


// -------------------------------------------------------------
// Most abstract Stream
// Use this for maximum flexibility
template < typename T >
class Stream
{
public:
    Stream( ){};
    virtual T next( );
    virtual T next( double deltaTime );
};

// -------------------------------------------------------------
/// Sometimes a Stream doesn't give a damn about `deltaTime`
/// so here's a default implementation discarding it.
template < typename T >
class ItemStream : public Stream< T >
{
public:
    ItemStream( ){};
    virtual T next( );
    T next( double deltaTime )
    {
        return next( );
    }
};

// -------------------------------------------------------------
/// Increment (and return) a value with each call to `next()`.
template < typename T >
class IncStream : public ItemStream< T >
{
private:
    T n;
    T increment;

public:
    IncStream( T start, T inc )
        : n( start )
        , increment( inc ){};
    T next( )
    {
        return n += increment;
    };
    T next( double )
    {
        return next( );
    };
};

// -------------------------------------------------------------
/// Generates single `Bullet*`.
class BulletStream : public ItemStream< Bullet* >
{
private:
    Stream< float >* angles;

public:
    BulletStream( Stream< float >* angleStream )
        : angles( angleStream ){};
    Bullet* next( )
    {
        return new Bullet( 300, 300, angles->next( ), 50 );
    };
};

// -------------------------------------------------------------
/// Takes multiple `Bullet*` and returns a `BulletArray*`.
class TakeStream : public ItemStream< BulletArray* >
{
private:
    int count;
    Stream< Bullet* >* stream;

public:
    TakeStream( int c, Stream< Bullet* >* from )
        : count( c )
        , stream( from ){};
    BulletArray* next( )
    {
        BulletArray* b = new BulletArray( );
        for ( int i = count; i > 0; i-- )
        {
            b->add( stream->next( ) );
        }
        return b;
    }
};

// -------------------------------------------------------------
/// Calls `next()` on a given stream in defined intervals (using `deltaTime`).
class IntervalStream : public Stream< BulletArray* >
{
private:
    double time;
    int counter;
    double interval;
    Stream< BulletArray* >* stream;

public:
    IntervalStream( double ival, Stream< BulletArray* >* from )
        : time( 0.0d )
        , counter( 0 )
        , interval( ival )
        , stream( from ){};
    BulletArray* next( )
    {
        return NULL;
    }
    BulletArray* next( double deltaTime )
    {
        BulletArray* b = NULL;
        time += deltaTime;
        float tfloor = floor( time / interval );
        if ( tfloor > counter )
        {
            counter = tfloor;
            b = stream->next( );
        }
        return b;
    }
};
