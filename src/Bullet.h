#pragma once

const int BULLET_SIZE = 24;
const int BULLET_COUNT = 1000;

class Bullet
{
public:
    ofVec2f position;
    ofVec2f direction;  // normalized
    float speed;
    float ghosting;

    Bullet( )
    {
        speed = 100.0f;
        ghosting = 0;
        position = ofVec2f( 300, 300 );
        direction = ofVec2f( ( ofRandom( 10 ) - 5 ) * 10,
                             ( ofRandom( 10 ) - 5 ) * 10 )
                        .normalize( );
    }

    /* Bullet( int x, int y, int dx, int dy ) */
    /* { */
    /*     speed = 100.0f; */
    /*     ghosting = 0; */
    /*     position = ofVec2f( x, y ); */
    /*     direction = ofVec2f( dx, dy ); */
    /* } */

    Bullet( int x, int y, float angle, float speed )
    {
        position = ofVec2f( x, y );
        direction = ofVec2f( cos( angle ), sin( angle ) );
        this->speed = speed;
        ghosting = 0;
    }
};

class BulletArray
{
public:
    int count;
    Bullet* bullets[10];
    BulletArray( )
        : count( 0 ){};
    void add( Bullet* b )
    {
        bullets[count++] = b;
    }
};

namespace BullOps
{
Bullet* bullets[BULLET_COUNT];

bool add( Bullet* b )
{
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        if ( bullets[i] == NULL )
        {
            bullets[i] = b;
            return true;
        }
    }
    return false;
}

void remove( int i )
{
    Bullet* bobo = bullets[i];
    delete ( bobo );
    bullets[i] = NULL;
}

/**
 * @return True if bullet should be removed.
 */
bool move( Bullet* b, double& deltaTime )
{
    if ( b == NULL )
    {
        return false;
    }
    b->position += b->direction * b->speed * deltaTime;
    if ( ( b->position.x > ( 600 + BULLET_SIZE ) )
         || ( b->position.x < ( 0 - BULLET_SIZE ) )
         || ( b->position.y > ( 600 + BULLET_SIZE ) )
         || ( b->position.y < ( 0 - BULLET_SIZE ) ) )
    {
        return true;
    }
    /* else if ( false ) */
    /* { */

    /* } */
    return false;
}

void moveAll( double deltaTime )
{
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        if ( bullets[i] == NULL )
        {
            continue;
        }
        if ( bullets[i]->ghosting > 0 )
        {
            bullets[i]->ghosting -= deltaTime;
        }
        bool rem = move( bullets[i], deltaTime );
        if ( rem )
        {
            remove( i );
        }
    }
}

void draw( Bullet* b, ofImage& img )
{
    if ( b != NULL )
    {
        img.draw( b->position, BULLET_SIZE, BULLET_SIZE );
    }
}

void drawAll( ofImage& img )
{
    ofSetColor( 64, 64, 200 );
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        draw( bullets[i], img );
    }
}

#define DIR bullets[i]->direction
#define POS bullets[i]->position

/// @todo touching multiple bullets?
int firstTouch( ofVec2f pt, float radius )
{
    float testDist = ( BULLET_SIZE / 2 ) + radius;
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        if ( bullets[i] == NULL )
        {
            continue;
        }
        else if ( ( POS.x < pt.x - testDist )
                  || ( POS.x > pt.x + testDist )
                  || ( POS.y < pt.y - testDist )
                  || ( POS.y > pt.y + testDist ) )
        {
            continue;
        }
        else if ( bullets[i]->ghosting > 0 )
        {
            continue;
        }
        ofVec2f dist = bullets[i]->position - pt;
        if ( dist.length( ) < testDist )
        {
            return i;
            break;
        }
    }
    return -1;
}

void reflect( ofVec2f center, float radius, int i )
{
    // not working: reflect at angle
    // ofVec2f pointAtCenter = center - POS;
    // float angle = DIR.angle( pointAtCenter );
    // DIR.rotate( 180 - abs( angle * 2 ) );
    bullets[i]->ghosting = 0.2;
    DIR *= -1;
    // not working: pull bullets out of intersection
    /* float depth = ( radius + ( BULLET_SIZE / 2 ) ) */
    /*               - pointAtCenter.length( ); */
    /* POS += DIR * ( depth / radius ); */
    // dir *= -1;
}

#undef dir
#undef pos
}
