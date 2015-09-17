#include "ofApp.h"

const int BULLET_SIZE = 24;
const int BULLET_COUNT = 100;

class Bullet
{
public:
    ofVec2f position;
    ofVec2f direction;
    bool active;
    Bullet( )
    {
        active = true;
        position = ofPoint( 300, 300 );
        // direction = ofPoint( 5, 0 );
        direction = ofPoint( ofRandom( 10 ) - 5, ofRandom( 10 ) - 5 );
    }
    Bullet( int x, int y, int dx, int dy )
    {
        active = true;
        position = ofPoint( x, y );
        direction = ofPoint( dx, dy );
    }
};

namespace BullOps
{
void move( Bullet* b, double& deltaTime )
{
    if ( b != NULL )
    {
        b->position += b->direction * deltaTime;
    }
}
void draw( Bullet* b, ofImage& img )
{
    if ( b != NULL )
    {
        img.draw( b->position, BULLET_SIZE, BULLET_SIZE );
    }
}
}

Bullet* bullets[BULLET_COUNT];

//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    bullet.loadImage( "bullet.png" );
    // for ( int i = BULLET_COUNT - 1; i >= 0; i-- )
    // {
    //     if ( i % 2 != 0 )
    //     {
    //         bullets[i] = new Bullet( );
    //     }
    // }
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
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
