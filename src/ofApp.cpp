#include "ofApp.h"

class Player
{
public:
    ofVec2f position;
    ofVec2f direction;
    int size;
    ofImage img;
    Player( ofImage img )
    {
        this->img = img;
        size = 32;
        position = ofVec2f( 300, 300 );
        direction = ofVec2f( 0, 0 );
    }
    void move( )
    {
        position += direction;
    }
    void draw( )
    {
        ofSetColor( 200, 92, 92 );
        img.draw( position, size, size );
    }
};

Player* player;

//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    circle.loadImage( "bullet.png" );
    player = new Player( circle );
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
    // timer & bullet creation
    Bullet* spawn = spawner.update( deltaTime );
    if ( spawn != NULL )
    {
        BullOps::add( spawn );
    }
    BullOps::moveAll( deltaTime );
}

//--------------------------------------------------------------
void ofApp::draw( )
{
    ofSetColor( 64, 64, 200 );
    BullOps::drawAll( circle );
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
