#pragma once

class Player
{
public:
    // game variables
    ofVec2f position;
    ofVec2f direction;
    int size;       // diameter (not radius)
    float health;   // finite
    float stamina;  // regenerates
    float breath;   // pause before regenerating stamina
    bool blocking;  // blocking
    bool hurting;   // visual aid when hit
    // config
    int runCursorDistance;  // distance (player to cursor)
                            // at which player runs
    float runningSpeed;
    float runningExhaustRate;
    float walkingSpeed;
    float breathPause;

    Player( )
    {
        health = 100;
        stamina = 100;
        breath = 0.0f;
        size = 24;
        position = ofVec2f( 300, 200 );
        direction = ofVec2f( 0, 0 );
        //
        runCursorDistance = 70;
        runningSpeed = 120;
        runningExhaustRate = 45;
        walkingSpeed = 45;
        breathPause = 1.0f;
    }

    void hurt( float amount )
    {
        hurting = true;
        health -= amount;
        health = max( 0.0f, health );
    }

    void exhaust( float amount )
    {
        stamina -= amount;
        breath = breathPause;
        if ( stamina < 0 )
        {
            hurt( -1 * stamina );
            stamina = 0;
        }
    }

    void update( double deltaTime )
    {
        if ( breath == 0.0f )
        {
            stamina += deltaTime * 25;
            stamina = min( 100.0f, stamina );
        }
        else
        {
            breath -= deltaTime;
            breath = max( 0.0f, breath );
        }
        if ( hurting )
        {
            // hurting is true for 1 frame (for visual effect)
            hurting = false;
        }
    }

    void move( int x, int y, double deltaTime )
    {
        if ( blocking )
        {
            return;
        }
        ofVec2f diff
            = ofVec2f( x - position.x, y - position.y );
        direction = diff;
        direction.normalize( );
        // depending on the player-to-cursor-distance,
        // the player walks (slow) or runs (fast)
        if ( ( diff.length( ) > runCursorDistance )
             && ( stamina > 0 ) )
        {
            // running
            direction *= runningSpeed;
            stamina -= runningExhaustRate * deltaTime;
            breath = breathPause;
        }
        else
        {
            // walking
            direction *= walkingSpeed * ( diff.length( )
                                          / runCursorDistance );
        }
        position += direction * deltaTime;
    }

#define AURA_ALPHA 32

    void draw( ofImage& img )
    {
        // aura
        if ( hurting )
        {
            ofSetColor( 0, AURA_ALPHA );
        }
        else if ( blocking )
        {
            ofSetColor( 92, 200, 92, AURA_ALPHA );
        }
        else
        {
            ofSetColor( 200, 92, 92, AURA_ALPHA );
        }
        img.draw( position, runCursorDistance * 2,
                  runCursorDistance * 2 );
        // player
        if ( hurting )
        {
            ofSetColor( 255 );
        }
        else if ( blocking )
        {
            ofSetColor( 64, 150, 64 );
        }
        else
        {
            ofSetColor( 200, 92, 92 );
        }
        img.draw( position, size, size );
        // stats
        ofSetColor( 192, 0, 32, 128 );
        ofRect( 0, 0, health * 6, 20 );
        ofSetColor( 92, 200, 0, 128 );
        ofRect( 0, 20, stamina * 6, 20 );
    }

#undef AURA_ALPHA
};
