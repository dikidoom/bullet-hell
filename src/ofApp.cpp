#include "ofApp.h"

const int BULLET_SIZE = 24;
const int BULLET_COUNT = 100;

class Bullet
{
public:
    ofVec2f position;
    ofVec2f direction;
    Bullet( )
    {
        position = ofPoint( 300, 300 );
        // direction = ofPoint( 5, 0 );
        direction = ofPoint( ofRandom( 10 ) - 5, ofRandom( 10 ) - 5 );
    }
    Bullet( int x, int y, int dx, int dy )
    {
        position = ofPoint( x, y );
        direction = ofPoint( dx, dy );
    }
};

namespace BullOps
{
void move( Bullet& b )
{
    b.position += b.direction;
}
void draw( Bullet& b, ofImage& img )
{
    img.draw( b.position, BULLET_SIZE, BULLET_SIZE );
}
}

Bullet bullets[BULLET_COUNT];

//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    bullet.loadImage( "bullet.png" );
    bullets[0] = Bullet( 300, 300, -5, 0 );
    // bullets[0] = new Bullet();
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
    // bullets[0].direction.rotate( 90 * deltaTime );
    // bullets[0].position += bullets[0].direction;
    for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    {
        BullOps::move( bullets[i] );
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
