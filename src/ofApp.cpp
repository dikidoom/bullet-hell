#include "ofApp.h"
#include "Bullet.h"
#include "Stream.h"
#include "Spawner.h"
#include "Player.h"

class Wall
{
public:
    ofVec2f origin;
    ofVec2f dimension;
    float angle;
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
    BulletArray* spawn = spawner.update( deltaTime );
    if ( spawn != NULL )
    {
        for ( int i = spawn->count - 1; i >= 0; i-- )
        {
            BullOps::add( spawn->bullets[i] );
        }
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
            player->exhaust( 40 );
            BullOps::reflect( player->position,
                              player->size / 2, touch );
        }
        else
        {
            player->hurt( 30 );
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
