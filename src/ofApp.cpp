#include "ofApp.h"
#include "Bullet.h"
#include "Spawner.h"

class Player
{
public:
    ofVec2f position;
    ofVec2f direction;
    int size;       // diameter (not radius)
    float health;   // finite
    float stamina;  // regenerates
    float regenBlock;
    bool hurt;
    Player( )
    {
        health = 100;
        stamina = 100;
        regenBlock = 0.0f;
        size = 24;
        position = ofVec2f( 300, 300 );
        direction = ofVec2f( 0, 0 );
    }
    void update( double deltaTime )
    {
        if ( regenBlock == 0.0f )
        {
            stamina += deltaTime * 25;
            stamina = min( 100.0f, stamina );
        }
        else
        {
            regenBlock -= deltaTime;
            regenBlock = max( 0.0f, regenBlock );
        }
        if( hurt ){
            health -= deltaTime * 50;
            health = max( 0.0f, health );
        }
        hurt = false;
    }
    void move( int x, int y, double deltaTime )
    {
        ofVec2f diff = ofVec2f( x - position.x, y - position.y );
        direction = diff;
        direction.normalize( );
        if ( ( diff.length( ) > 45 ) && ( stamina > 0 ) )
        {
            direction *= 90;
            stamina -= 30 * deltaTime;
            regenBlock = 1.0f;
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
        if ( hurt )
        {
            ofSetColor( 0, 92 );
        }
        else
        {
            ofSetColor( 200, 92, 92, 92 );
        }
        img.draw( position, 90, 90 );  /// @todo magic number
        // player
        if ( hurt )
        {
            ofSetColor( 255 );
        }
        else
        {
            ofSetColor( 200, 92, 92 );
        }
        img.draw( position, size, size );
        //
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
    // timer & bullet creation
    Bullet* spawn = spawner.update( deltaTime );
    if ( spawn != NULL )
    {
        BullOps::add( spawn );
    }
    BullOps::moveAll( deltaTime );
    // player
    player->update( deltaTime );
    player->move( mouseX, mouseY, deltaTime );
    player->hurt = BullOps::touching( player->position, player->size / 2 );
}

//--------------------------------------------------------------
void ofApp::draw( )
{
    ofSetColor( 64, 64, 200 );
    BullOps::drawAll( circle );
    player->draw( circle );
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
