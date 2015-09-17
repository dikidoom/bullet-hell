#pragma once

const int BULLET_SIZE = 24;
const int BULLET_COUNT = 1000;

class Bullet
{
public:
    ofVec2f position;
    ofVec2f direction;
    Bullet( )
    {
        position = ofVec2f( 300, 300 );
        direction = ofVec2f( ( ofRandom( 10 ) - 5 ) * 10,
                             ( ofRandom( 10 ) - 5 ) * 10 );
    }
    Bullet( int x, int y, int dx, int dy )
    {
        position = ofVec2f( x, y );
        direction = ofVec2f( dx, dy );
    }
    Bullet( int x, int y, float angle, float speed )
    {
        position = ofVec2f( x, y );
        direction = ofVec2f( cos( angle ) * speed, sin( angle ) * speed );
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
    if ( b != NULL )
    {
        b->position += b->direction * deltaTime;
        if ( ( b->position.x > ( 600 + BULLET_SIZE ) )
             || ( b->position.x < ( 0 - BULLET_SIZE ) )
             || ( b->position.y > ( 600 + BULLET_SIZE ) )
             || ( b->position.y < ( 0 - BULLET_SIZE ) ) )
        {
            return true;
        }
    }
    return false;
}
void moveAll( double deltaTime )
{
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
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
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        draw( bullets[i], img );
    }
}
bool touching( ofVec2f pt, float radius )
{
    float testDist = ( BULLET_SIZE / 2 ) + radius;
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        if ( bullets[i] == NULL )
        {
            continue;
        }
        ofVec2f dist = bullets[i]->position - pt;
        if ( dist.length( ) < testDist )
        {
            return true;
            break;
        }
    }
    return false;
}
}
