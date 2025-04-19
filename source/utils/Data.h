#ifndef DATA_H
#define DATA_H

#include <cstdio>
#include <fstream>

#include "utils/Constants.h"
#include "utils/json.hpp"
#include "utils//Support.h"

using json = nlohmann::json;

class Data
{
    Data();
    static json::value_type rawReadValue(json jvalue, const char *name);
    static Data * getObject();
public:
    json::value_type readValue(const char *name);

    static float getCollisionRoughness();

    class Game{
        static json::value_type getGame();
    public:
        static bool getDebugView();
        static bool getDebugExitView();
        static bool getEnabledFPSAtStart();
        static bool getApplyShaders();
        static bool getEnableLaggingTests();
    };

    class Player{
        static json::value_type getPlayer();
    public:
        static float getSpeedStraight();
        static int getHealthPoints();
        static int getAmmo();
    };

    class Enemy{
        static json::value_type getEnemy();
    public:
        static float getSpeedDecreaseRandomness();
        static float getSpeedIncreaseRandomness();
        static float getDealDamageDelay();
        static float getDealDamageLagDeterminer();

        class Ghost{
            static json::value_type getGhost();
        public:
            static float getMovementSpeed();
            static float getDamage();
            static float getHealth();
        };

        class Zombie{
            static json::value_type getZombie();
        public:
            static float getMovementSpeed();
            static float getDamage();
            static float getHealth();
        };
    };

    class EnemySpawner{
        static json::value_type getEnemySpawner();
    public:
        static float getSpawnDistanceToScreen();
        static int getSpawnDelayMS();
    };

private:
    json json_;
};

#endif // DATA_H
