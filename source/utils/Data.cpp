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

json::value_type Data::readValue(const char *name)
{
    return rawReadValue(json_, name);
}

Data *Data::getObject()
{
    static Data data;
    return &data;
}




json::value_type Data::Game::getGame()
{
    return Data::getObject()->readValue("game");
}

bool Data::Game::getDebugView()
{
    return Data::rawReadValue(Game::getGame(), "debug view");
}

bool Data::Game::getDebugExitView()
{
    return Data::rawReadValue(Game::getGame(), "debug exit app");
}

bool Data::Game::getEnabledFPSAtStart()
{
    return Data::rawReadValue(Game::getGame(), "enabled fps at start");
}
bool Data::Game::getApplyShaders()
{
    return Data::rawReadValue(Game::getGame(), "apply shaders");
}





json::value_type Data::Player::getPlayer()
{
    return Data::getObject()->readValue("player");
}

float Data::Player::getSpeedStraight()
{
    return Data::rawReadValue(Player::getPlayer(), "speed straight");
}

int Data::Player::getHealthPoints()
{
    return Data::rawReadValue(Player::getPlayer(), "health points");
}

int Data::Player::getAmmo()
{
    return Data::rawReadValue(Player::getPlayer(), "ammo");
}




json::value_type Data::Enemy::getEnemy()
{
    return Data::getObject()->readValue("enemy");
}

float Data::Enemy::getSpeedDecreaseRandomness()
{
    return Data::rawReadValue(Enemy::getEnemy(), "speed decrease randomness");
}

float Data::Enemy::getSpeedIncreaseRandomness()
{
    return Data::rawReadValue(Enemy::getEnemy(), "speed increase randomness");
}

float Data::Enemy::getDealDamageDelay()
{
    return Data::rawReadValue(Enemy::getEnemy(), "deal damage delay units");
}

float Data::Enemy::getDealDamageLagDeterminer()
{
    return Data::rawReadValue(Enemy::getEnemy(), "deal damage lag determiner");
}





json::value_type Data::Enemy::Ghost::getGhost()
{
    return Data::rawReadValue(Enemy::getEnemy(), "ghost");
}

float Data::Enemy::Ghost::getMovementSpeed()
{
    return Data::rawReadValue(Ghost::getGhost(), "movement speed");
}

float Data::Enemy::Ghost::getDamage()
{
    return Data::rawReadValue(Ghost::getGhost(), "damage");
}

float Data::Enemy::Ghost::getHealth()
{
    return Data::rawReadValue(Ghost::getGhost(), "health");
}

json::value_type Data::EnemySpawner::getEnemySpawner()
{
    return Data::getObject()->readValue("enemy spawner");
}

float Data::EnemySpawner::getSpawnDistanceToScreen()
{
    return Data::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn distance to screen");
}

int Data::EnemySpawner::getSpawnDelayMS()
{
    return Data::rawReadValue(EnemySpawner::getEnemySpawner(), "spawn delay ms");
}

json::value_type Data::Enemy::Zombie::getZombie()
{
    return Data::rawReadValue(Enemy::getEnemy(), "zombie");
}

float Data::Enemy::Zombie::getMovementSpeed()
{
    return Data::rawReadValue(Zombie::getZombie(), "movement speed");
}

float Data::Enemy::Zombie::getDamage()
{
    return Data::rawReadValue(Zombie::getZombie(), "damage");
}

float Data::Enemy::Zombie::getHealth()
{
    return Data::rawReadValue(Zombie::getZombie(), "health");
}
