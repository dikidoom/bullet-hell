#pragma once

class Spawner
{
public:
    Stream< BulletArray* >* stream;
    Spawner( )
        : stream( new IntervalStream(
              0.2,
              new TakeStream(
                  3,
                  new BulletStream( new IncStream< double >(
                      0, PI / 4 ) ) ) ) )
    {
    }
    /**
     * @return Bullets to spawn, NULL if not
     */
    BulletArray* update( double deltaTime )
    {
        BulletArray* b = stream->next( deltaTime );
        return b;
    }
};
