#include "ofApp.h"
#include "Bullet.h"

Bullet* bullets[BULLET_COUNT];

double timer = 0.0d;
int timerLastFired = 0;
float bulletAngle = 0.0f;

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
    timer += deltaTime;
    if ( floor( timer * 10 ) > timerLastFired )
    {
        timerLastFired = floor( timer );
        for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
        {
            if ( bullets[i] == NULL )
            {
                bullets[i] = new Bullet( 300, 300, bulletAngle, 100.0f );
                bulletAngle += 10;
                break;
            }
        }
    }
    // moving bullets
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        BullOps::move( bullets[i], deltaTime );
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
