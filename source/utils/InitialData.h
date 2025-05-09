#ifndef INITIALDATA_H
#define INITIALDATA_H

#include <SFML/Graphics.hpp>

#include <cstdio>

#include "utils/Constants.h"
#include "utils/json.hpp"

using json = nlohmann::json;

class InitialData
{
    InitialData();
    static json::value_type rawReadValue(json jvalue, const char *name);
    static InitialData * getObject();
public:
    json::value_type readValue(const char *name);

    static float getCollisionRoughness();
    static float getTextureUpdateDelayMS();
    static float getSpriteScale();
    static float getBoundsThickness();
    static sf::Color getBoundsColor();
    static bool getShowAllBounds();

    class Game{
        static json::value_type getGame();
    public:
        static bool getDebugView();
        static bool getDebugExitView();
        static bool getEnabledFPSAtStart();
        static bool getApplyShaders();
        static bool getEnableLaggingTests();

        static float getTargetWidth();
        static float getTargetHeight();
    };

    class Play{
        static json::value_type getPlay();
    public:
        static float getMaxDealtDamageHandledByDamageAnimation();
        static int getStatInfoDisplayDelayMS();
    };

    class Player{
        static json::value_type getPlayer();
    public:
        static float getSpeedStraight();
        static int getHealthPoints();
        static bool getShowBounds();
        static sf::Color getDefaultSkinColor();
        static sf::Color getDefaultShirtColor();
        static sf::Color getDefaultBackpackColor();
    };

    class Weapon{
        static json::value_type getWeapon();
    public:
        static int getAmmo();
        static int getShotDelayMS(uint weaponIndex);
        static float getDamage(uint weaponIndex);
    };

    class Bullet{
        static json::value_type getBullet();
    public:
        static int getMovementSpeed();
        static bool getShowBounds();
        static float getAliveDistanceFromWindowEdge();
    };

    class Armor{
        static json::value_type getArmor();
    public:
        static float getMaxArmorProtection();
        static float getHelemtProtection(uint armorIndex);
        static float getChestProtection(uint armorIndex);
        static float getArmsProtection(uint armorIndex);
        static float getForearmsProtection(uint armorIndex);
        static float getGlovesProtection(uint armorIndex);
    };

    class Enemy{
        static json::value_type getEnemy();
    public:
        static float getSpeedDecreaseRandomness();
        static float getSpeedIncreaseRandomness();
        static float getMoneyDecreaseRandomness();
        static float getMoneyIncreaseRandomness();
        static float getAttackDelayMS();
        static int getSpeedIncreaseTimeDelayMS();
        static float getSpeedIncreaseTimeAmountMultiplier();
        static bool getShowBounds();

        class Ghost{
            static json::value_type getGhost();
        public:
            static float getMovementSpeed();
            static float getDamage();
            static float getHealth();
            static float getPlayerMoveSlowDownRatio();
        };

        class Zombie{
            static json::value_type getZombie();
        public:
            static float getMovementSpeed(uint zombieType);
            static float getDamage(uint zombieType);
            static float getHealthPoints(uint zombieType);
            static float getPlayerMoveSlowDownRatio(uint zombieType);
            static float getSpawnChance(uint zombieType);
            static float getNetWorth(uint zombieType);
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

#endif // INITIALDATA_H
