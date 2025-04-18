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
        Support::displayEndingAppError(snOut);
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
        Support::displayEndingAppError(snOut);
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
            "Cannot read key '%s'\n"
            "JSON error: \n"
            "%s", name, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayEndingAppError(snOut);
        exit(1);
    }
    if(value.is_null())
    {
        char snOut[128];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Reading key from JSON failed!\n"
            "Cannot read key '%s'", name);
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayEndingAppError(snOut);
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

float Data::Enemy::getDefaultSpeed()
{
    return Data::rawReadValue(Enemy::getEnemy(), "default speed");
}

float Data::Enemy::getSpeedDecreaseRandomness()
{
    return Data::rawReadValue(Enemy::getEnemy(), "speed decrease randomness");
}

float Data::Enemy::getSpeedIncreaseRandomness()
{
    return Data::rawReadValue(Enemy::getEnemy(), "speed increase randomness");
}





json::value_type Data::Enemy::Ghost::getGhost()
{
    return Data::rawReadValue(Enemy::getEnemy(), "ghost");
}

float Data::Enemy::Ghost::getDefaultSpeed()
{
    return Data::rawReadValue(Ghost::getGhost(), "default speed");
}
