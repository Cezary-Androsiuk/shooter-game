#include "Data.h"

Data::Data() {

    std::ifstream iFile(DATA_FILE_NAME);
    if(!iFile.good())
    {
        char snOut[49 + strlen(DATA_FILE_NAME) -2 /* -2 is %s signature */];
        const int snOutSize = sizeof(snOut);
        int requiredSize =
            snprintf(
                snOut,
                sizeof(snOut),
                "Oppening data file failed!\n"
                "Cannot open file '%s'",
                DATA_FILE_NAME
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
            "%s", DATA_FILE_NAME, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayApplicationError(snOut);
        exit(1);
    }

    iFile.close();
}

json::value_type Data::rawReadValue(json jvalue, const char *name)
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

Data *Data::getObject()
{
    static Data data;
    return &data;
}

json::value_type Data::readValue(const char *name)
{
    return rawReadValue(json_, name);
}

float Data::getCollisionRoughness()
{
    static const float value =
        Data::getObject()->readValue("collision roughness");
    return value;
}




json::value_type Data::Game::getGame()
{
    static const json::value_type game =
        Data::getObject()->readValue("game");
    return game;
}

bool Data::Game::getDebugView()
{
    static const bool value =
        Data::rawReadValue(Game::getGame(), "debug view");
    return value;
}

bool Data::Game::getDebugExitView()
{
    static const bool value =
        Data::rawReadValue(Game::getGame(), "debug exit app");
    return value;
}

bool Data::Game::getEnabledFPSAtStart()
{
    static const bool value =
        Data::rawReadValue(Game::getGame(), "enabled fps at start");
    return value;
}
bool Data::Game::getApplyShaders()
{
    static const bool value =
        Data::rawReadValue(Game::getGame(), "apply shaders");
    return value;
}

bool Data::Game::getEnableLaggingTests()
{
    static const bool value =
        Data::rawReadValue(Game::getGame(), "enable lagging tests");
    return value;
}





json::value_type Data::Player::getPlayer()
{
    static const json::value_type player =
        Data::getObject()->readValue("player");
    return player;
}

float Data::Player::getSpeedStraight()
{
    static const float value =
        Data::rawReadValue(Player::getPlayer(), "speed straight");
    return value;
}

int Data::Player::getHealthPoints()
{
    static const int value =
        Data::rawReadValue(Player::getPlayer(), "health points");
    return value;
}

int Data::Player::getAmmo()
{
    static const int value =
        Data::rawReadValue(Player::getPlayer(), "ammo");
    return value;
}




json::value_type Data::Enemy::getEnemy()
{
    static const json::value_type enemy =
        Data::getObject()->readValue("enemy");
    return enemy;
}

float Data::Enemy::getSpeedDecreaseRandomness()
{
    static const float value =
        Data::rawReadValue(Enemy::getEnemy(), "speed decrease randomness");
    return value;
}

float Data::Enemy::getSpeedIncreaseRandomness()
{
    static const float value =
        Data::rawReadValue(Enemy::getEnemy(), "speed increase randomness");
    return value;
}

float Data::Enemy::getDealDamageDelay()
{
    static const float value =
        Data::rawReadValue(Enemy::getEnemy(), "deal damage delay units");
    return value;
}

float Data::Enemy::getDealDamageLagDeterminer()
{
    static const float value =
        Data::rawReadValue(Enemy::getEnemy(), "deal damage lag determiner");
    return value;
}





json::value_type Data::Enemy::Ghost::getGhost()
{
    static const json::value_type ghost =
        Data::rawReadValue(Enemy::getEnemy(), "ghost");
    return ghost;
}

float Data::Enemy::Ghost::getMovementSpeed()
{
    static const float value =
        Data::rawReadValue(Ghost::getGhost(), "movement speed");
    return value;
}

float Data::Enemy::Ghost::getDamage()
{
    static const float value =
        Data::rawReadValue(Ghost::getGhost(), "damage");
    return value;
}

float Data::Enemy::Ghost::getHealth()
{
    static const float value =
        Data::rawReadValue(Ghost::getGhost(), "health");
    return value;
}

float Data::Enemy::Ghost::getPlayerMoveSlowDownRatio()
{
    static const float value =
        Data::rawReadValue(Ghost::getGhost(), "player move slow down ratio");
    return value;
}



json::value_type Data::EnemySpawner::getEnemySpawner()
{
    static const json::value_type enemySpawner =
        Data::getObject()->readValue("enemy spawner");
    return enemySpawner;
}

float Data::EnemySpawner::getSpawnDistanceToScreen()
{
    static const float value =
        Data::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn distance to screen");
    return value;
}

int Data::EnemySpawner::getSpawnDelayMS()
{
    static const int value =
        Data::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn delay ms");
    return value;
}





json::value_type Data::Enemy::Zombie::getZombie()
{
    static const json::value_type zombie =
        Data::rawReadValue(Enemy::getEnemy(), "zombie");
    return zombie;
}

float Data::Enemy::Zombie::getMovementSpeed()
{
    static const float value =
        Data::rawReadValue(Zombie::getZombie(), "movement speed");
    return value;
}

float Data::Enemy::Zombie::getDamage()
{
    static const float value =
        Data::rawReadValue(Zombie::getZombie(), "damage");
    return value;
}

float Data::Enemy::Zombie::getHealth()
{
    static const float value =
        Data::rawReadValue(Zombie::getZombie(), "health");
    return value;
}

float Data::Enemy::Zombie::getPlayerMoveSlowDownRatio()
{
    static const float value =
        Data::rawReadValue(Zombie::getZombie(), "player move slow down ratio");
    return value;
}
