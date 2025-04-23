#include "PlayState.h"

#include "utils/GlobalData.h"
#include "utils/Support.h"
#include "animations/GotDamageAnimation.h"

void PlayState::initData()
{
    m_bullets.reserve(64);
    m_animations.reserve(128);

    m_statInfoDisplayDelay = InitialData::Play::getStatInfoDisplayDelayMS();
    m_sessionTime.restart();
    m_sesionMoney = 0.f;
}

void PlayState::initMap()
{
    m_map = std::make_shared<Map>();
    m_map->buildObstacles();
}

void PlayState::initPlayer()
{
    m_player = Player::getInstance();
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();

    m_player->setPosition(sf::Vector2f(windowSize.x/2.f, windowSize.y/2.f));
    m_player->setAvailableAreaForPlayer(m_map);
    m_player->setEnemies(&m_enemies);
    m_player->resetHealtPoints();

    /// forces to first release left mouse button before shoting
    /// because oppening this stage is always with key pressed after pressing start button
    printf("test\n");
    fflush(stdout);
    m_player->getWeapon()->rememberIfMouseButtonClicked();
}

void PlayState::initEnemySpawner()
{

}

void PlayState::initObjects()
{
    this->initMap();
    this->initPlayer();
    this->initEnemySpawner();
}

void PlayState::initStatInfo()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    /// NOTCH
    m_statInfoNotch = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getPlayStatInfoNotchTexture(),
        sf::IntRect(0,0, 800, 90));
    m_statInfoNotch->setScale(windowRatio);
    m_statInfoNotch->setPosition(sf::Vector2f((1920.f/2 - 800.f/2) * windowRatio.x, 0.f ));

    /// MONEY
    m_moneyLabel = std::make_unique<sgui::Label>();
    m_moneyLabel->setFont(GlobalData::getInstance()->getFontInkFree());
    m_moneyLabel->setString("Money: 0$");
    m_moneyLabel->setCharacterSize(20);
    sf::Vector2f moneyLabelSize = m_moneyLabel->getSize();
    m_moneyLabel->setPosition(sf::Vector2f((1920.f/2 - 250) * windowRatio.x -moneyLabelSize.x/2, 10.f* windowRatio.y));

    /// TIME
    m_timeLabel = std::make_unique<sgui::Label>();
    m_timeLabel->setFont(GlobalData::getInstance()->getFontInkFree());
    m_timeLabel->setString("Time: 00:00s");
    m_timeLabel->setCharacterSize(20);
    sf::Vector2f timeLabelSize = m_timeLabel->getSize();
    m_timeLabel->setPosition(sf::Vector2f((1920.f/2) * windowRatio.x -timeLabelSize.x/2, 10.f* windowRatio.y));

    /// PLAYER HEALTH POINTS
    m_playerHealthPointsLabel = std::make_unique<sgui::Label>();
    m_playerHealthPointsLabel->setFont(GlobalData::getInstance()->getFontInkFree());
    m_playerHealthPointsLabel->setString("Health: 1000");
    m_playerHealthPointsLabel->setCharacterSize(20);
    sf::Vector2f playerHealthPoinsLabelSize = m_playerHealthPointsLabel->getSize();
    m_playerHealthPointsLabel->setPosition(
        sf::Vector2f((1920.f/2 + 250) * windowRatio.x -playerHealthPoinsLabelSize.x/2,
                     10.f* windowRatio.y));
}

PlayState::PlayState()
{
    printf("created playstate\n");
    fflush(stdout);
}

PlayState::~PlayState()
{

}

void PlayState::init()
{
    this->initData();
    this->initObjects();
    this->initStatInfo();
}

bool PlayState::requestDefeatState()
{
    return !m_player->getPlayerAlive();
}

void PlayState::updatePlayer()
{
    m_player->update();

    std::unique_ptr<Bullet> bullet = m_player->getWeapon()->getBulletFromShot();
    if(bullet)
    {
        m_bullets.push_back(std::unique_ptr<Bullet>(bullet.release()));
    }

}

void PlayState::updateEnemySpawner()
{
    m_enemySpawner.update();
    std::shared_ptr<Enemy> enemy = m_enemySpawner.createdEnemy();
    if(!enemy)
    {
        return;
    }

    m_enemies.push_back(enemy);

    enemy->setPlayerBounds(m_player->getBounds());
    enemy->setAvailableAreaForEnemy(m_map);

}

void PlayState::updateEnemies()
{
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        Enemy *enemy = (*it).get();
        enemy->update();

        /// deletes the object if not alive
        if (!enemy->getEnemyAlive()) {
            it = m_enemies.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayState::updatePlayerAndEnemiesRelation()
{
    const FloatRectEdges playerBounds(*m_player->getBounds());
    for(const auto &enemy : m_enemies)
    {
        const FloatRectEdges enemyBounds(enemy->getBounds());

        /// +2 is required because collision detection is performed somewere else
        const float overlapLeft   = playerBounds.right+2 - enemyBounds.left;
        const float overlapRight  = enemyBounds.right - playerBounds.left+2;
        const float overlapTop    = playerBounds.bottom+2 - enemyBounds.top;
        const float overlapBottom = enemyBounds.bottom - playerBounds.top+2;

        if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
        {
            // static int i =0;
            // printf("occur %d\n", i++);
            // fflush(stdout);

            if(enemy->getReadyToAttack())
            {
                m_player->dealDamage(enemy->getDamage());
                m_animations.push_back(
                    std::make_unique<GotDamageAnimation>());
            }
        }
    }
}

void PlayState::updateBullets()
{
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        Bullet *bullet = (*it).get();
        bullet->update();

        /// deletes the object if out side the screen
        if (bullet->getReadyToDie()) {
            it = m_bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayState::updateBulletsAndEnemiesRelation()
{
    for(const auto &enemy : m_enemies)
    {
        const FloatRectEdges enemyBounds(enemy->getBounds());

        for (auto it = m_bullets.begin(); it != m_bullets.end(); )
        {
            Bullet *bullet = (*it).get();
            const FloatRectEdges bulletBounds(bullet->getBounds());

            const float overlapLeft   = bulletBounds.right - enemyBounds.left;
            const float overlapRight  = enemyBounds.right - bulletBounds.left;
            const float overlapTop    = bulletBounds.bottom - enemyBounds.top;
            const float overlapBottom = enemyBounds.bottom - bulletBounds.top;

            if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
            {
                enemy->dealDamage(bullet->getDamage());

                /// add money for player and the session
                if(!enemy->getEnemyAlive())
                {
                    int enemyNetWorth = enemy->getNetWorth();
                    m_player->addMoney(enemyNetWorth);
                    m_sesionMoney += enemyNetWorth;
                }

                /// deletes the bullet because hit he enemy
                it = m_bullets.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void PlayState::updateStatInfo()
{
    if(m_statInfoDisplayClock.getElapsedTime().asMilliseconds() < m_statInfoDisplayDelay)
        return;
    m_statInfoDisplayClock.restart();

    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();


    constexpr int bufferSize = 32;
    char snOut[bufferSize] = {0};
    int requiredSize;

    /// set text
    m_sesionMoney = round(m_sesionMoney * 100) / 100.f; /// to make sure, but shoud be rounded
    requiredSize = snprintf(snOut, bufferSize, "Money: %d$", (int)m_sesionMoney);
    Support::informAboutToSmallBuffer(requiredSize, bufferSize);
    m_moneyLabel->setString(snOut);

    /// set text
    m_survivedSeconds = m_sessionTime.getElapsedTime().asMilliseconds() / 1000;
    int secondsElapsed = m_survivedSeconds % 60;
    int minutesElapsed = secondsElapsed / 60;
    requiredSize = snprintf(snOut, bufferSize, "Time: %02d:%02ds",
                                minutesElapsed, secondsElapsed);
    Support::informAboutToSmallBuffer(requiredSize, bufferSize);
    m_timeLabel->setString(snOut);

    /// set text
    requiredSize = snprintf(snOut, bufferSize, "Health: %d", m_player->getHealthPoints());
    Support::informAboutToSmallBuffer(requiredSize, bufferSize);
    m_playerHealthPointsLabel->setString(snOut);

    /// set size
    sf::Vector2f moneyLabelSize = m_moneyLabel->getSize();
    m_moneyLabel->setPosition(sf::Vector2f((1920.f/2 - 250) * windowRatio.x -moneyLabelSize.x/2, 10.f* windowRatio.y));

    /// set size
    sf::Vector2f timeLabelSize = m_timeLabel->getSize();
    m_timeLabel->setPosition(sf::Vector2f((1920.f/2) * windowRatio.x -timeLabelSize.x/2, 10.f* windowRatio.y));

    /// set size
    sf::Vector2f playerHealthPoinsLabelSize = m_playerHealthPointsLabel->getSize();
    m_playerHealthPointsLabel->setPosition(
        sf::Vector2f((1920.f/2 + 250) * windowRatio.x -playerHealthPoinsLabelSize.x/2,
                     10.f* windowRatio.y));

    /// update
    m_moneyLabel->update();
    m_timeLabel->update();
    m_playerHealthPointsLabel->update();
}

void PlayState::updateAnimations()
{
    for (auto it = m_animations.begin(); it != m_animations.end(); ) {
        Animation *animation = (*it).get();
        animation->update();

        /// deletes the object if out side the screen
        if (animation->getFinished()) {
            it = m_animations.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayState::renderStatInfo(sf::RenderTarget *target)
{
    target->draw(*m_statInfoNotch);
    m_moneyLabel->render(target);
    m_timeLabel->render(target);
    m_playerHealthPointsLabel->render(target);
}

void PlayState::pollEvent(const sf::Event &event)
{
    m_enemySpawner.pollEvent(event);
    m_player->pollEvent(event);
\
    for(const auto &bullet : m_bullets)
        bullet->pollEvent(event);
}

void PlayState::update()
{
    this->updatePlayer();
    this->updateEnemySpawner();
    this->updateEnemies();
    this->updatePlayerAndEnemiesRelation();
    this->updateBullets();
    this->updateBulletsAndEnemiesRelation();

    this->updateStatInfo();

    this->updateAnimations();
}

void PlayState::render(sf::RenderTarget *target)
{
    m_map->render(target);

    for(const auto &enemy : m_enemies)
        enemy->render(target);

    for(const auto &bullet : m_bullets)
        bullet->render(target);

    m_player->render(target);

    for(const auto &animation : m_animations)
        animation->render(target);

    this->renderStatInfo(target);
}

float PlayState::getEarnedMoney() const
{
    return m_sesionMoney;
}

int PlayState::getSurvivedSeconds() const
{
    return m_survivedSeconds;
}
