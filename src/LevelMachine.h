#ifndef LEVELMACHINEN_H_
#define LEVELMACHINEN_H_

#include "EnemyManager.h"

enum WAVE_SIZE {SIZE_ERROR, SIZE_SMALL, SIZE_MEDIUM};
//Base for all possible combinations of spawn patterns.
class BaseWave
{
    protected:
        EnemyManager& tEnemies;
        WAVE_SIZE size;
    public:
        BaseWave(EnemyManager& tEnm) : tEnemies(tEnm) {size = SIZE_ERROR;}
        virtual void spawn() = 0;
        WAVE_SIZE getSize() {return size;}
};

class WandererWave : public BaseWave
{
    public:
        WandererWave(EnemyManager& tEnm) : BaseWave(tEnm) {size = SIZE_SMALL;}
        void spawn();
};

class RunstrikeWave : public BaseWave
{
    public:
        RunstrikeWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_SMALL;}
        void spawn();
};

class SidewinderWave : public BaseWave
{
    public:
        SidewinderWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_SMALL; }
        void spawn();
};

class VampireWave : public BaseWave
{
    public:
        VampireWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_MEDIUM;}
        void spawn();
};

class BlasterWave : public BaseWave
{
    public:
        BlasterWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_MEDIUM;}
        void spawn();
};

class CircleStraferWave : public BaseWave
{
    public:
        CircleStraferWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_MEDIUM; }
        void spawn();
};

class GreenFighterWave : public BaseWave
{
    public:
        GreenFighterWave(EnemyManager& tEnm) : BaseWave(tEnm) { size = SIZE_MEDIUM; }
        void spawn();
};

class LevelMachine
{
    private:
        static std::vector<BaseWave*> WavePool;
        EnemyManager& tEnemies;
    public:
        LevelMachine(EnemyManager& tEnm) : tEnemies(tEnm) {}
        static void addWavePool(BaseWave* wave) {WavePool.push_back(wave);}
        void think();
};

#endif // LEVELMACHINEN_H_
