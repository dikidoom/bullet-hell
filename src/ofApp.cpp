#include "ofApp.h"
#include "Bullet.h"
#include "Spawner.h"

Bullet* bullets[BULLET_COUNT];
Spawner spawner;

//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    bullet.loadImage( "bullet.png" );
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
    // timer & bullet creation
    Bullet* spawn = spawner.update( deltaTime );
    if ( spawn != NULL )
    {
        for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
        {
            if ( bullets[i] == NULL )
            {
                bullets[i] = spawn;
                break;
            }
        }
    }
    // moving bullets
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        bool remove = BullOps::move( bullets[i], deltaTime );
        if ( remove )
        {
            Bullet* bobo = bullets[i];
            delete ( bobo );
            bullets[i] = NULL;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw( )
{
    ofSetColor( 64, 64, 200 );
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        BullOps::draw( bullets[i], bullet );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key )
{
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
}

//--------------------------------------------------------------
void ofApp::mouseReleased( int x, int y, int button )
{
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
