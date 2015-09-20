#pragma once

class Spawner
{
public:
    double timer;
    int timerLastFired;
    float bulletAngle;
    // IncStream<float> angles;
    // BulletStream bstream;
    CountStream cstream;
    Spawner( )
        : timer( 0.0d )
        , timerLastFired( 0 )
        , bulletAngle( 0.0f )
        //, angles( 0, PI / 2 )
        //, bstream( new IncStream< float >( 0, PI / 8 ) )
        , cstream( 4,
                   new BulletStream(
                       new IncStream< float >( 0, PI / 12 ) ) )
    {
    }
    /**
     * @return Bullets to spawn, NULL if not
     */
    BulletArray* update( double deltaTime )
    {
        BulletArray* b = NULL;
        timer += deltaTime;
        float tfloor = floor( timer * 7 );
        if ( tfloor > timerLastFired )
        {
            timerLastFired = tfloor;
            b = cstream.next( );
            /* b = new Bullet( */
            /*     300, 300, angles.next( ),  // bulletAngle, */
            /*     50.0f + ( ( timerLastFired % 7 ) * 10 ) ); */
            // bulletAngle += PI / 12;
        }
        return b;
    }
};
