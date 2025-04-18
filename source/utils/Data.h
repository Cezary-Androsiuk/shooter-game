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

    class Game{
        static json::value_type getGame();
    public:
        static bool getDebugView();
        static bool getDebugExitView();
        static bool getEnabledFPSAtStart();
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

        static float getDefaultSpeed();
        static float getSpeedDecreaseRandomness();
        static float getSpeedIncreaseRandomness();

        class Ghost{
            static json::value_type getGhost();
        public:
            static float getDefaultSpeed();
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
