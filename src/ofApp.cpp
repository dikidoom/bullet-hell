#include "ofApp.h"
#include "Bullet.h"
#include "Spawner.h"

class Player
{
public:
    ofVec2f position;
    ofVec2f direction;
    int size;          // diameter (not radius)
    float health;      // finite
    float stamina;     // regenerates
    float catchBreath;  // 1 second pause before regenerating
                       // stamina
    bool blocking;        // blocking
    bool hurting;         // visual aid when hit
    Player( )
    {
        health = 100;
        stamina = 100;
        catchBreath = 0.0f;
        size = 24;
        position = ofVec2f( 300, 200 );
        direction = ofVec2f( 0, 0 );
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
        catchBreath = 1.0f;
        if( stamina < 0 ){
            hurt( -1 * stamina );
            stamina = 0;
        }
    }
    void update( double deltaTime )
    {
        if ( catchBreath == 0.0f )
        {
            stamina += deltaTime * 25;
            stamina = min( 100.0f, stamina );
        }
        else
        {
            catchBreath -= deltaTime;
            catchBreath = max( 0.0f, catchBreath );
        }
        if ( hurting )
        {
            // health -= deltaTime * 50;
            // health = max( 0.0f, health );
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
        if ( ( diff.length( ) > 45 ) && ( stamina > 0 ) )
        {
            direction *= 90;
            stamina -= 30 * deltaTime;
            catchBreath = 1.0f;
        }
        else
        {
            direction *= 45;
        }
        position += direction * deltaTime;
    }
    void draw( ofImage& img )
    {
        // aura
        if ( hurting )
        {
            ofSetColor( 0, 92 );
        }
        else if ( blocking )
        {
            ofSetColor( 92, 200, 92, 92 );
        }
        else
        {
            ofSetColor( 200, 92, 92, 92 );
        }
        img.draw( position, 90, 90 );  /// @todo magic number
        // player
        if ( hurting )
        {
            ofSetColor( 255 );
        }
        else if ( blocking )
        {
            ofSetColor( 92, 200, 92 );
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
};

Player* player;
Spawner spawner;

//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    ofHideCursor( );  // doesnt work on ubuntu 15.04 ?
    circle.loadImage( "bullet.png" );
    circle.setAnchorPercent( .5, .5 );
    player = new Player( );
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
    // timer & bullets
    Bullet* spawn = spawner.update( deltaTime );
    if ( spawn != NULL )
    {
        BullOps::add( spawn );
    }
    BullOps::moveAll( deltaTime );
    // player
    player->update( deltaTime );
    player->move( mouseX, mouseY, deltaTime );
    int touch = BullOps::firstTouch( player->position,
                                     player->size / 2 );
    if ( touch > -1 )
    {
        if ( player->blocking )
        {
            player->exhaust( 20 );
            BullOps::reflect( player->position,
                              player->size / 2, touch );
        }
        else
        {
            player->hurt( 20 );
            BullOps::remove( touch );
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw( )
{
    BullOps::drawAll( circle );
    player->draw( circle );
    //
    ofSetColor( 0, 0, 0, 92 );
    ofLine( 300, 0, 300, 600 );
    ofLine( 0, 300, 600, 300 );
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key )
{
    // if ( key == 'a' )
    // {
    //     player->direction = ofVec2f( -5, 0 );
    // }
}

//--------------------------------------------------------------
void ofApp::keyReleased( int key )
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved( int x, int y )
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged( int x, int y, int button )
{
}

//--------------------------------------------------------------
void ofApp::mousePressed( int x, int y, int button )
{
    player->blocking = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased( int x, int y, int button )
{
    player->blocking = false;
}

//--------------------------------------------------------------
void ofApp::windowResized( int w, int h )
{
}

//--------------------------------------------------------------
void ofApp::gotMessage( ofMessage msg )
{
}

//--------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo dragInfo )
{
}
