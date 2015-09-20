#pragma once

// composition order:
// dt ---------------------->|
// sequence -> composition -> time -> count -> bullet -> angle
//                                                    -> speed
//                                    |<------ bullet
// |<-------------------------------- bulletarray

template < typename T >
class Stream
{
public:
    Stream( ){};
    virtual T next( );
};

template < typename T >
class IncStream : public Stream< T >
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
};

class BulletStream : public Stream< Bullet* >
{
private:
    Stream< float >* angles;

public:
    BulletStream( Stream< float >* ang )
        : angles( ang ){};
    Bullet* next( )
    {
        return new Bullet( 300, 300, angles->next( ), 50 );
    };
};

class CountStream : public Stream< BulletArray* >
{
private:
    int count;
    Stream< Bullet* >* stream;

public:
    CountStream( int c, Stream< Bullet* >* from )
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

/* template < typename T > */
/* class TimeStream */
/* { */
/* public: */
/*     TimeStream( ){}; */
/*     virtual T next( double dt ); */
/* } */

/* class IntervalStream : TimeStream< Bullet > */
/* { */
/* private: */
/*     double time; */
/*     double interval; */
/*     int counter; */

/* public: */
/*     IntervalStream( double iv ) */
/*         : time( 0 ) */
/*         , interval( iv ) */
/*         , counter( 0 ){}; */
/*     Bullet */
/* }  */
