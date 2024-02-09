#include "LevelMachine.h"

void WandererWave::spawn()
{
    //Base, Delay, Amount, Interval
    tEnemies.addWave<Wanderer>(new Wanderer(-25, -25, 50, 50), 0, 5, 1.0f);
    tEnemies.addWave<Wanderer>(new Wanderer(-25, -25, 50, 50, true), 0, 5, 1.0f);
}

void RunstrikeWave::spawn()
{
    float curDelay = 0;
    for(int z = 1; z <= 2; z++)
    {
        for(int i = 40; i <= 960; i += 40)
        {
            float delay = ((float)(i / 40) * 0.2f) + curDelay;
            tEnemies.addWave<Runstrike>(new Runstrike(i, -45), delay, 1, 0);

            if( i == 960)
                curDelay = delay;
        }
        for(int i = 960; i >= 40; i -= 40)
        {
            float delay = ((float)((960 - i) / 40) * 0.2f) + curDelay + 0.3f;
            tEnemies.addWave<Runstrike>(new Runstrike(i - 20, -45), delay, 1, 0);

            if(i == 40)
                curDelay = delay;
        }
    }
}

void SidewinderWave::spawn()
{
    for(int i = 1; i <= 5; i++)
    {
        int yPos = 40 + (i * 40);
        tEnemies.addWave<Sidewinder>(new Sidewinder(-45, yPos), 0, 5, 1);
        tEnemies.addWave<Sidewinder>(new Sidewinder(1024 - 45, yPos, true), 0, 5, 1);
    }
}

void VampireWave::spawn()
{
    tEnemies.addWave<Vampire_Outer>(new Vampire_Outer((1024 / 2) - 48, -25), 1.0f, 1, 1.0f);
    tEnemies.addWave<Vampire_Outer>(new Vampire_Outer((1024 / 2) - 48, -25, true), 1.0f, 1, 1.0f);
    tEnemies.addWave<Vampire_Inner>(new Vampire_Inner((1024 / 2) - 48, -25), 1.0f, 1, 1.0f);
}

void BlasterWave::spawn()
{
    tEnemies.addWave<Blaster>(new Blaster((1024 / 2) + 25, -25), 0, 30, 0.4f);
    tEnemies.addWave<Blaster>(new Blaster((1024 / 2) - 25, -25, true), 0, 30, 0.4f);
}

void CircleStraferWave::spawn()
{
    tEnemies.addWave<CircleStrafer>(new CircleStrafer((1024 / 2) + 30, -25), 1.0f, 10, 2.0f);
    tEnemies.addWave<CircleStrafer>(new CircleStrafer((1024 / 2) - 30, -25, true), 1.0f, 10, 2.0f);
}

void GreenFighterWave::spawn()
{
    tEnemies.addWave<GreenFighter>(new GreenFighter(-25, -25), 0, 3, 5.0f);
    tEnemies.addWave<GreenFighter>(new GreenFighter(1024 + 25, -25, true), 0, 3, 5.0f);
}
std::vector<BaseWave*> LevelMachine::WavePool;

void LevelMachine::think()
{
    if(tEnemies.isEmpty())
    {
        int numWavesToSpawn = 1;//sf::Randomizer::Random(1, 2);
        for(int i = 0; i < numWavesToSpawn; i++)
        {
            //Generate a random number
            int enemyIndex = sf::Randomizer::Random(0, WavePool.size() - 1);
            WavePool.at(enemyIndex)->spawn();
        }
    }
}
