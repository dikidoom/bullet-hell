#pragma once

class Spawner
{
public:
    double timer;
    int timerLastFired;
    float bulletAngle;
    Spawner( )
        : timer( 0.0d )
        , timerLastFired( 0 )
        , bulletAngle( 0.0f )
    {
    }
    /**
     * @return Bullet to spawn, NULL if not
     */
    Bullet* update( double deltaTime )
    {
        Bullet* b = NULL;
        timer += deltaTime;
        float tfloor = floor( timer * 7 );
        if ( tfloor > timerLastFired )
        {
            timerLastFired = tfloor;
            b = new Bullet( 300, 300, bulletAngle, 100.0f );
            bulletAngle += PI / 12;
        }
        return b;
    }
};
