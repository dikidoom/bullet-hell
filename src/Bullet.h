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
        position = ofPoint( 300, 300 );
        direction = ofPoint( ( ofRandom( 10 ) - 5 ) * 10,
                             ( ofRandom( 10 ) - 5 ) * 10 );
    }
    Bullet( int x, int y, int dx, int dy )
    {
        position = ofPoint( x, y );
        direction = ofPoint( dx, dy );
    }
    Bullet( int x, int y, float angle, float speed )
    {
        position = ofPoint( x, y );
        direction = ofPoint( cos( angle ) * speed, sin( angle ) * speed );
    }
};

namespace BullOps
{
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
void draw( Bullet* b, ofImage& img )
{
    if ( b != NULL )
    {
        img.draw( b->position, BULLET_SIZE, BULLET_SIZE );
    }
}
}
