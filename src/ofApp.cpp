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
Stream< BulletArray* >* streems[4];
int streemIndex = 0;

double foo[2] = {0.0d, 1.0d};  // start times
double bar[2] = {2.0d, 3.0d};  // end times
Stream< BulletArray* >* baz[2] = {
    new IntervalStream(
        0.25d, new TakeStream( 1, new BulletStream( 0, 50 ) ) ),
    new IntervalStream(
        0.25d,
        new TakeStream( 1, new BulletStream( PI / 2, 50 ) ) )};
//--------------------------------------------------------------
void ofApp::setup( )
{
    ofSetWindowShape( 600, 600 );
    ofHideCursor( );  // doesnt work on ubuntu 15.04 ?
    circle.loadImage( "bullet.png" );
    circle.setAnchorPercent( .5, .5 );
    player = new Player( );
    streems[0] = new IntervalStream(
        1, new TakeStream(
               6, new BulletStream( new IncStream< double >(
                      0, PI / 12 ) ) ) );
    streems[1] = new IntervalStream(
        0.3, new TakeStream(
                 1, new BulletStream( new IncStream< double >(
                        0, PI / 2 ) ) ) );
    streems[2] = new IntervalStream(
        0.1, new TakeStream(
                 1, new BulletStream( new IncStream< double >(
                        0, PI / 24 ) ) ) );
    double* foo = new double[2]{0.0, 1.0};
    double* bar = new double[2]{2.0, 3.0};
    Stream< BulletArray* >** baz
        = new Stream< BulletArray* >[2]{
            new IntervalStream(
                0.25d, new TakeStream(
                           1, new BulletStream( 0, 50 ) ) ),
            new IntervalStream(
                0.25d, new TakeStream( 1, new BulletStream(
                                              PI / 2, 50 ) ) )};

    streems[3] = new SequenceStream( 2, foo, bar, baz );
}

//--------------------------------------------------------------
void ofApp::update( )
{
    double deltaTime = ofGetLastFrameTime( );
    // timer & bullets
    // BulletArray* spawn = spawner.update( deltaTime );
    BulletArray* spawn
        = streems[streemIndex]->next( deltaTime );
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
    switch ( key )
    {
    case '1':
        streemIndex = 0;
        break;
    case '2':
        streemIndex = 1;
        break;
    case '3':
        streemIndex = 2;
        break;
    case '4':
        streemIndex = 3;
        break;
    default:
        break;
    };
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
