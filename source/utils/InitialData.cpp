#include "InitialData.h"

#include <fstream>

#include "utils/Constants.h"
#include "utils/Support.h"

InitialData::InitialData() {

    std::ifstream iFile(INITIAL_DATA_FILE_PATH);
    if(!iFile.good())
    {
        char snOut[49 + strlen(INITIAL_DATA_FILE_PATH) -2 /* -2 is %s signature */];
        const int snOutSize = sizeof(snOut);
        int requiredSize =
            snprintf(
                snOut,
                sizeof(snOut),
                "Oppening data file failed!\n"
                "Cannot open file '%s'",
                INITIAL_DATA_FILE_PATH
            );
        Support::informAboutToSmallBuffer(requiredSize, snOutSize);

        /// testing
        // for(int i=0; i<snOutSize; i++)
        //     printf("'%c':%d\n", snOut[i], snOut[i]);
        // fflush(stdout);
        Support::displayApplicationError(snOut);
        exit(1);
    }

    try
    {
        json_ = json::parse(iFile);
    }
    catch(const std::exception &e)
    {
        char snOut[512];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Parse data file to JSON failed!\n"
            "Cannot parse file '%s'\n"
            "JSON error: \n"
            "%s", INITIAL_DATA_FILE_PATH, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayApplicationError(snOut);
        exit(1);
    }

    iFile.close();

    printf("initialize data (json) loaded\n");
    fflush(stdout);
}

json::value_type InitialData::rawReadValue(json jvalue, const char *name)
{
    json::value_type value;
    try {
        value = jvalue[name];
    }
    catch (const std::exception &e)
    {
        char snOut[512];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Reading key from JSON failed!\n"
            "Cannot read key '%s' from initial data\n"
            "JSON error: \n"
            "%s", name, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayApplicationError(snOut);
        exit(1);
    }
    if(value.is_null())
    {
        char snOut[128];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Reading key from JSON failed!\n"
            "Cannot read key '%s' from initial data.", name);
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayApplicationError(snOut);
        exit(1);
    }
    return value;
}

InitialData *InitialData::getObject()
{
    static InitialData data;
    return &data;
}

json::value_type InitialData::readValue(const char *name)
{
    return rawReadValue(json_, name);
}

float InitialData::getCollisionRoughness()
{
    static const float value =
        InitialData::getObject()->readValue("collision roughness");
    return value;
}

float InitialData::getTextureUpdateDelayMS()
{
    static const float value =
        InitialData::getObject()->readValue("texture update delay ms");
    return value;
}

float InitialData::getSpriteScale()
{
    static const float value =
        InitialData::getObject()->readValue("sprite scale");
    return value;
}

float InitialData::getBoundsThickness()
{
    static const float value =
        InitialData::getObject()->readValue("bounds thickness");
    return value;
}

sf::Color InitialData::getBoundsColor()
{
    static const json::value_type color =
        InitialData::getObject()->readValue("bounds color");

    static const uint red = color["red"];
    static const uint green = color["green"];
    static const uint blue = color["blue"];
    static const uint alpha = color["alpha"];

    return sf::Color(red, green, blue, alpha);
}

bool InitialData::getShowAllBounds()
{
    static const bool value =
        InitialData::getObject()->readValue("show all bounds");
    return value;
}




json::value_type InitialData::Game::getGame()
{
    static const json::value_type game =
        InitialData::getObject()->readValue("game");
    return game;
}

bool InitialData::Game::getDebugView()
{
    static const bool value =
        InitialData::rawReadValue(Game::getGame(), "debug view");
    return value;
}

bool InitialData::Game::getDebugExitView()
{
    static const bool value =
        InitialData::rawReadValue(Game::getGame(), "debug exit app");
    return value;
}

bool InitialData::Game::getEnabledFPSAtStart()
{
    static const bool value =
        InitialData::rawReadValue(Game::getGame(), "enabled fps at start");
    return value;
}
bool InitialData::Game::getApplyShaders()
{
    static const bool value =
        InitialData::rawReadValue(Game::getGame(), "apply shaders");
    return value;
}

bool InitialData::Game::getEnableLaggingTests()
{
    static const bool value =
        InitialData::rawReadValue(Game::getGame(), "enable lagging tests");
    return value;
}

float InitialData::Game::getTargetWidth()
{
    static const float value =
        InitialData::rawReadValue(Game::getGame(), "target width");
    return value;
}

float InitialData::Game::getTargetHeight()
{
    static const float value =
        InitialData::rawReadValue(Game::getGame(), "target height");
    return value;
}





json::value_type InitialData::Play::getPlay()
{
    static const json::value_type play =
        InitialData::getObject()->readValue("play");
    return play;
}

float InitialData::Play::getMaxDealtDamageHandledByDamageAnimation()
{
    static const float value =
        InitialData::rawReadValue(Play::getPlay(), "max dealt damage handled by damage animation");
    return value;
}

int InitialData::Play::getStatInfoDisplayDelayMS()
{
    static const float value =
        InitialData::rawReadValue(Play::getPlay(), "stat info display delay ms");
    return value;
}







json::value_type InitialData::Player::getPlayer()
{
    static const json::value_type player =
        InitialData::getObject()->readValue("player");
    return player;
}

float InitialData::Player::getSpeedStraight()
{
    static const float value =
        InitialData::rawReadValue(Player::getPlayer(), "speed straight");
    return value;
}

int InitialData::Player::getHealthPoints()
{
    static const int value =
        InitialData::rawReadValue(Player::getPlayer(), "health points");
    return value;
}

bool InitialData::Player::getShowBounds()
{
    static const bool value =
        InitialData::rawReadValue(Player::getPlayer(), "show bounds");
    return value;
}

sf::Color InitialData::Player::getDefaultSkinColor()
{
    static const json::value_type color =
        InitialData::rawReadValue(Player::getPlayer(), "default skin color");

    static const uint red = color["red"];
    static const uint green = color["green"];
    static const uint blue = color["blue"];
    static const uint alpha = color["alpha"];

    return sf::Color(red, green, blue, alpha);
}

sf::Color InitialData::Player::getDefaultShirtColor()
{
    static const json::value_type color =
        InitialData::rawReadValue(Player::getPlayer(), "default shirt color");

    static const uint red = color["red"];
    static const uint green = color["green"];
    static const uint blue = color["blue"];
    static const uint alpha = color["alpha"];

    return sf::Color(red, green, blue, alpha);
}

sf::Color InitialData::Player::getDefaultBackpackColor()
{
    static const json::value_type color =
        InitialData::rawReadValue(Player::getPlayer(), "default backpack color");

    static const uint red = color["red"];
    static const uint green = color["green"];
    static const uint blue = color["blue"];
    static const uint alpha = color["alpha"];

    return sf::Color(red, green, blue, alpha);
}





json::value_type InitialData::Weapon::getWeapon()
{
    static const json::value_type weapon =
        InitialData::getObject()->readValue("weapon");
    return weapon;
}

int InitialData::Weapon::getAmmo()
{
    static const int value =
        InitialData::rawReadValue(Weapon::getWeapon(), "ammo");
    return value;
}

int InitialData::Weapon::getShotDelayMS(uint weaponIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Weapon::getWeapon(), "shot delay ms");
    static const int values[WEAPON_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "weapon 0"),
        InitialData::rawReadValue(container, "weapon 1"),
        InitialData::rawReadValue(container, "weapon 2"),
        InitialData::rawReadValue(container, "weapon 3"),
        InitialData::rawReadValue(container, "weapon 4"),
        InitialData::rawReadValue(container, "weapon 5"),
        InitialData::rawReadValue(container, "weapon 6"),
        InitialData::rawReadValue(container, "weapon 7"),
        InitialData::rawReadValue(container, "weapon 8")
    };

    if(weaponIndex > WEAPON_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid weapon index, max is %u and got: %u. (using last instead)\n", WEAPON_TYPES_COUNT-1, weaponIndex);
        fflush(stderr);
        weaponIndex = WEAPON_TYPES_COUNT-1;
    }

    return values[weaponIndex];
}

float InitialData::Weapon::getDamage(uint weaponIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Weapon::getWeapon(), "damage");
    static const float values[WEAPON_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "weapon 0"),
        InitialData::rawReadValue(container, "weapon 1"),
        InitialData::rawReadValue(container, "weapon 2"),
        InitialData::rawReadValue(container, "weapon 3"),
        InitialData::rawReadValue(container, "weapon 4"),
        InitialData::rawReadValue(container, "weapon 5"),
        InitialData::rawReadValue(container, "weapon 6"),
        InitialData::rawReadValue(container, "weapon 7"),
        InitialData::rawReadValue(container, "weapon 8")
    };

    if(weaponIndex > WEAPON_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid weapon index, max is %u and got: %u. (using last instead)\n", WEAPON_TYPES_COUNT-1, weaponIndex);
        fflush(stderr);
        weaponIndex = WEAPON_TYPES_COUNT-1;
    }

    return values[weaponIndex];
}




json::value_type InitialData::Bullet::getBullet()
{
    static const json::value_type bullet =
        InitialData::getObject()->readValue("bullet");
    return bullet;
}

int InitialData::Bullet::getMovementSpeed()
{
    static const int value =
        InitialData::rawReadValue(Bullet::getBullet(), "movement speed");
    return value;
}

bool InitialData::Bullet::getShowBounds()
{
    static const bool value =
        InitialData::rawReadValue(Bullet::getBullet(), "show bounds");
    return value;
}

float InitialData::Bullet::getAliveDistanceFromWindowEdge()
{
    static const float value =
        InitialData::rawReadValue(Bullet::getBullet(), "alive distance from window edge");
    return value;
}





json::value_type InitialData::Armor::getArmor()
{
    static const json::value_type armor =
        InitialData::getObject()->readValue("armor");
    return armor;
}

float InitialData::Armor::getMaxArmorProtection()
{
    static const float value =
        InitialData::rawReadValue(Armor::getArmor(), "max armor protection");
    return value;
}

float InitialData::Armor::getHelemtProtection(uint armorIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Armor::getArmor(), "helmet protection");
    static const float values[ARMOR_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "armor 0"),
        InitialData::rawReadValue(container, "armor 1"),
        InitialData::rawReadValue(container, "armor 2"),
        InitialData::rawReadValue(container, "armor 3"),
        InitialData::rawReadValue(container, "armor 4"),
        InitialData::rawReadValue(container, "armor 5"),
    };

    if(armorIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armorIndex);
        fflush(stderr);
        armorIndex = ARMOR_TYPES_COUNT-1;
    }

    return values[armorIndex];
}

float InitialData::Armor::getChestProtection(uint armorIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Armor::getArmor(), "chest protection");
    static const float values[ARMOR_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "armor 0"),
        InitialData::rawReadValue(container, "armor 1"),
        InitialData::rawReadValue(container, "armor 2"),
        InitialData::rawReadValue(container, "armor 3"),
        InitialData::rawReadValue(container, "armor 4"),
        InitialData::rawReadValue(container, "armor 5"),
    };

    if(armorIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armorIndex);
        fflush(stderr);
        armorIndex = ARMOR_TYPES_COUNT-1;
    }

    return values[armorIndex];
}

float InitialData::Armor::getArmsProtection(uint armorIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Armor::getArmor(), "Arms protection");
    static const float values[ARMOR_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "armor 0"),
        InitialData::rawReadValue(container, "armor 1"),
        InitialData::rawReadValue(container, "armor 2"),
        InitialData::rawReadValue(container, "armor 3"),
        InitialData::rawReadValue(container, "armor 4"),
        InitialData::rawReadValue(container, "armor 5"),
    };

    if(armorIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armorIndex);
        fflush(stderr);
        armorIndex = ARMOR_TYPES_COUNT-1;
    }

    return values[armorIndex];
}

float InitialData::Armor::getForearmsProtection(uint armorIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Armor::getArmor(), "forearms protection");
    static const float values[ARMOR_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "armor 0"),
        InitialData::rawReadValue(container, "armor 1"),
        InitialData::rawReadValue(container, "armor 2"),
        InitialData::rawReadValue(container, "armor 3"),
        InitialData::rawReadValue(container, "armor 4"),
        InitialData::rawReadValue(container, "armor 5"),
    };

    if(armorIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armorIndex);
        fflush(stderr);
        armorIndex = ARMOR_TYPES_COUNT-1;
    }

    return values[armorIndex];
}

float InitialData::Armor::getGlovesProtection(uint armorIndex)
{
    static const json::value_type container =
        InitialData::rawReadValue(Armor::getArmor(), "gloves protection");
    static const float values[ARMOR_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "armor 0"),
        InitialData::rawReadValue(container, "armor 1"),
        InitialData::rawReadValue(container, "armor 2"),
        InitialData::rawReadValue(container, "armor 3"),
        InitialData::rawReadValue(container, "armor 4"),
        InitialData::rawReadValue(container, "armor 5"),
    };

    if(armorIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armorIndex);
        fflush(stderr);
        armorIndex = ARMOR_TYPES_COUNT-1;
    }

    return values[armorIndex];
}






json::value_type InitialData::Enemy::getEnemy()
{
    static const json::value_type enemy =
        InitialData::getObject()->readValue("enemy");
    return enemy;
}

float InitialData::Enemy::getSpeedDecreaseRandomness()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "speed decrease randomness");
    return value;
}

float InitialData::Enemy::getSpeedIncreaseRandomness()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "speed increase randomness");
    return value;
}

float InitialData::Enemy::getMoneyDecreaseRandomness()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "money decrease randomness");
    return value;
}

float InitialData::Enemy::getMoneyIncreaseRandomness()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "money increase randomness");
    return value;
}

float InitialData::Enemy::getAttackDelayMS()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "attack delay ms");
    return value;
}

int InitialData::Enemy::getSpeedIncreaseTimeDelayMS()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "speed increase time delay ms");
    return value;
}

float InitialData::Enemy::getSpeedIncreaseTimeAmountMultiplier()
{
    static const float value =
        InitialData::rawReadValue(Enemy::getEnemy(), "speed increase time amount multiplier");
    return value;
}

bool InitialData::Enemy::getShowBounds()
{
    static const bool value =
        InitialData::rawReadValue(Enemy::getEnemy(), "show bounds");
    return value;
}





json::value_type InitialData::Enemy::Ghost::getGhost()
{
    static const json::value_type ghost =
        InitialData::rawReadValue(Enemy::getEnemy(), "ghost");
    return ghost;
}

float InitialData::Enemy::Ghost::getMovementSpeed()
{
    static const float value =
        InitialData::rawReadValue(Ghost::getGhost(), "movement speed");
    return value;
}

float InitialData::Enemy::Ghost::getDamage()
{
    static const float value =
        InitialData::rawReadValue(Ghost::getGhost(), "damage");
    return value;
}

float InitialData::Enemy::Ghost::getHealth()
{
    static const float value =
        InitialData::rawReadValue(Ghost::getGhost(), "health");
    return value;
}

float InitialData::Enemy::Ghost::getPlayerMoveSlowDownRatio()
{
    static const float value =
        InitialData::rawReadValue(Ghost::getGhost(), "player move slow down ratio");
    return value;
}



json::value_type InitialData::EnemySpawner::getEnemySpawner()
{
    static const json::value_type enemySpawner =
        InitialData::getObject()->readValue("enemy spawner");
    return enemySpawner;
}

float InitialData::EnemySpawner::getSpawnDistanceToScreen()
{
    static const float value =
        InitialData::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn distance to screen");
    return value;
}

int InitialData::EnemySpawner::getSpawnDelayMS()
{
    static const int value =
        InitialData::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn delay ms");
    return value;
}





json::value_type InitialData::Enemy::Zombie::getZombie()
{
    static const json::value_type zombie =
        InitialData::rawReadValue(Enemy::getEnemy(), "zombie");
    return zombie;
}

float InitialData::Enemy::Zombie::getMovementSpeed(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "movement speed");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}

float InitialData::Enemy::Zombie::getDamage(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "movement speed");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}

float InitialData::Enemy::Zombie::getHealthPoints(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "health points");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}

float InitialData::Enemy::Zombie::getPlayerMoveSlowDownRatio(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "player move slow down ratio");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}

float InitialData::Enemy::Zombie::getSpawnChance(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "spawn chance");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}

float InitialData::Enemy::Zombie::getNetWorth(uint zombieType)
{
    static const json::value_type container =
        InitialData::rawReadValue(Zombie::getZombie(), "net worth");
    static const float values[ZOMBIE_TYPES_COUNT] = {
        InitialData::rawReadValue(container, "zombie 0"),
        InitialData::rawReadValue(container, "zombie 1"),
        InitialData::rawReadValue(container, "zombie 2"),
        InitialData::rawReadValue(container, "zombie 3"),
        InitialData::rawReadValue(container, "zombie 4"),
        InitialData::rawReadValue(container, "zombie 5")
    };

    if(zombieType > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid zombie type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, zombieType);
        fflush(stderr);
        zombieType = ZOMBIE_TYPES_COUNT-1;
    }

    return values[zombieType];
}
