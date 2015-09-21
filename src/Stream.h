#pragma once

// composition order:
// INPUTS:
// dt -------------------------->|
// sequence -> composition -> time -> count -> bullet -> angle
//                                                    -> speed
//                                    |<------ Bullet*
// |<-------------------------------- BulletArray*
// OUTPUTS:

// TODOS

// carousel (in1, in2, ..., inn ): each next() switches b/w in1,
// in2, ..., inn, in1, in2, ...)

/// @todo pre-emptively stop `double` times from overflowing

/// @todo should probably unify all streams so they are more
/// readily composable.

// how about: all streams return the same type?
// e.g. bulletarray?
// and take & relate the deltatime-argument
// (and just don't use it?)
// then we can mix and match freely?

// can Take/Count be called MultiPoll instead?

// should each stream return an object <value, stream>?
// so there's a StreamNext function that works on all streams
// and any composing function returns a stream object
// (although any stream having a `next` is almost the same?)

/// @todo add helper functions, e.g.
/// interval(args) -> return new IntervalStream(args) and
/// take(args) -> return new TakeStream(args)

/// @todo rename BulletStream to SingleBulletStream / ShotStream
/// and use BulletStream as a Synonym for Stream< BullerArray* >

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
    };
};

// -------------------------------------------------------------
/// Other times a Stream ONLY works WITH `deltaTime`
/// so here's a default implementation bugging out on `next()`.
template < typename T >
class TimeStream : public Stream< T >
{
public:
    TimeStream( ){};
    T next( )
    {
        return NULL;
    };
    virtual T next( double deltaTime );
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
/// Return the same value for each call to `next()`.
template < typename T >
class ConstStream : public ItemStream< T >
{
private:
    T n;

public:
    ConstStream( T n )
        : n( n ){};
    T next( )
    {
        return n;
    };
};

// -------------------------------------------------------------
/// Generates single `Bullet*`.
class BulletStream : public ItemStream< Bullet* >
{
private:
    Stream< double >* angles;
    Stream< double >* speeds;

public:
    BulletStream( Stream< double >* angleStream )
        : angles( angleStream )
        , speeds( new ConstStream< double >( 50 ) ){};
    BulletStream( double angle, double speed )
        : angles( new ConstStream< double >( angle ) )
        , speeds( new ConstStream< double >( speed ) ){};
    Bullet* next( )
    {
        return new Bullet( 300, 300, angles->next( ),
                           speeds->next( ) );
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
    };
};

// -------------------------------------------------------------
/// Calls `next()` on a given stream in defined intervals (using
/// `deltaTime`).
class IntervalStream : public TimeStream< BulletArray* >
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
    };
};

// -------------------------------------------------------------
/// Invoke a set of streams in timed sequence.
class SequenceStream : public TimeStream< BulletArray* >
{
private:
    double time;
    double repeatTime;
    int sequenceCount;
    double* startTimes;
    double* endTimes;
    Stream< BulletArray* >** streams;

public:
    SequenceStream( int sCount,
                    double* sTimes,
                    double* eTimes,
                    Stream< BulletArray* >* ss[] )
        : time( 0.0d )
        , repeatTime( 0.0d )
        , sequenceCount( sCount )
        , startTimes( sTimes )
        , endTimes( eTimes )
        , streams( ss )
    {
        // adjust looping time
        for ( int i = sequenceCount; i >= 0; i-- )
        {
            if ( endTimes[i] > repeatTime )
            {
                repeatTime = endTimes[i];
            }
        }
    };
    BulletArray* next( double deltaTime )
    {
        time += deltaTime;
        if ( time > repeatTime )
        {
            time -= repeatTime;
        }
        BulletArray* b = NULL;
        for ( int i = sequenceCount - 1; i >= 0; i-- )
        {
            if ( ( time >= startTimes[i] )
                 && ( time <= endTimes[i] ) )
            {
                if ( b == NULL )
                {
                    b = streams[i]->next( deltaTime );
                }
                else
                {
                    b->add( streams[i]->next( deltaTime ) );
                }
            }
        }
        return b;
    };
};

// -------------------------------------------------------------
/// @todo Use multiple streams at the same time.
