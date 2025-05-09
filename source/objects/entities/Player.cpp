#include "Player.h"

#include "utils/InitialData.h"
#include "utils/DeltaTime.h"
#include "utils/GlobalData.h"
#include "utils/AdvancedComputation.h"

void Player::initData()
{
    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;

    // m_points = 0;
    // m_headCount = 0;
    m_money = 0.f;
    m_healthPoints = InitialData::Player::getHealthPoints();

    m_movementSpeedAddons.msStraightDefault = InitialData::Player::getSpeedStraight();
    m_movementSpeedAddons.msMultiplier = 1.0;
}

void Player::deserializeData()
{

}

void Player::initRenderModel()
{
    // m_renderModel.bounds.setPosition(m_position); /// position is (0,0)
    m_boundsShape.setFillColor(sf::Color::Transparent);
    m_boundsShape.setSize(m_size);
    m_boundsShape.setOutlineColor(InitialData::getBoundsColor());
    m_boundsShape.setOutlineThickness(InitialData::getBoundsThickness());
    m_boundsVisible = InitialData::Player::getShowBounds() || InitialData::getShowAllBounds();

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::PLAYER_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::PLAYER_FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::PLAYER_FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::PLAYER_FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int objectYPos = frameOffsetY;
    m_renderModel.bounds.setTexture(mainSpriteTexture, false);
    m_renderModel.bounds.setTextureRect(
        sf::IntRect(frameOffsetX, objectYPos, frameSizeX, frameSizeY));
    m_renderModel.bounds.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_renderModel.bounds.setScale(spriteScale, spriteScale);

    objectYPos += frameSizeY;
    m_renderModel.skin.setTexture(mainSpriteTexture, false);
    m_renderModel.skin.setTextureRect(
        sf::IntRect(frameOffsetX, objectYPos, frameSizeX, frameSizeY));
    m_renderModel.skin.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_renderModel.skin.setScale(spriteScale, spriteScale);
    m_renderModel.skin.setColor(InitialData::Player::getDefaultSkinColor());

    objectYPos += frameSizeY;
    m_renderModel.shirt.setTexture(mainSpriteTexture, false);
    m_renderModel.shirt.setTextureRect(
        sf::IntRect(frameOffsetX, objectYPos, frameSizeX, frameSizeY));
    m_renderModel.shirt.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_renderModel.shirt.setScale(spriteScale, spriteScale);
    m_renderModel.shirt.setColor(InitialData::Player::getDefaultShirtColor());

    objectYPos += frameSizeY;
    m_renderModel.bakpack.setTexture(mainSpriteTexture, false);
    m_renderModel.bakpack.setTextureRect(
        sf::IntRect(frameOffsetX, objectYPos, frameSizeX, frameSizeY));
    m_renderModel.bakpack.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_renderModel.bakpack.setScale(spriteScale, spriteScale);
    m_renderModel.bakpack.setColor(InitialData::Player::getDefaultBackpackColor());

}

void Player::initWeapon()
{
    if(!m_weapon)
        m_weapon = std::make_unique<Weapon>();

    // m_weapon->setWeaponIndex(8);

    m_weapon->setPlayerSize(m_size);
    m_weapon->init();

    // m_weapon->setWeaponIndex(8);
}

void Player::initArmor()
{
    if(!m_armor)
        m_armor = std::make_unique<Armor>();

    m_armor->setPlayerCenter(&m_center);
    m_armor->setPlayerRotationAngle(&m_rotationAngle);

    // m_armor->setHelmet(5);
    // m_armor->setChest(5);
    // m_armor->setArms(5);
    // m_armor->setForearms(5);
    // m_armor->setGloves(5);

    m_armor->init();
}

void Player::initEquipment()
{
    this->initWeapon();
    this->initArmor();
}

void Player::serializeData()
{

}

Player::Player()
{

}

Player::~Player()
{
    this->serializeData();
}

Player *Player::getInstance()
{
    static Player player;
    return &player;
}

void Player::move(float moveX, float moveY)
{
    m_moveVector.x = moveX;
    m_moveVector.y = moveY;

    m_position = sf::Vector2f(
        m_position.x + moveX,
        m_position.y + moveY
    );
}

void Player::updateMovementSpeed()
{
    m_movementSpeedStraight = m_movementSpeedAddons.msStraightDefault *
                              m_movementSpeedAddons.msMultiplier *
                              DeltaTime::get()->value();
    m_movementSpeedOblique = m_movementSpeedStraight / 1.4142f /* sqrt(2) */;
}

void Player::limitMoveThatEnterEnemy(
    const FloatRectEdges &playerBounds, std::shared_ptr<Enemy> enemy)
{
    ///
    /// NOTE: move this logic to PlayState class
    ///
    const FloatRectEdges enemyBounds(enemy->getBounds());

    const float overlapLeft   = playerBounds.right - enemyBounds.left;
    const float overlapRight  = enemyBounds.right - playerBounds.left;
    const float overlapTop    = playerBounds.bottom - enemyBounds.top;
    const float overlapBottom = enemyBounds.bottom - playerBounds.top;

    // bool p = DeltaTime::canPrint();

    // const float dt = DeltaTime::get()->value();
    const float enemyNewtons = enemy->getSize().x *
                               enemy->getSize().y *
                               enemy->getMovementSpeed();
    const float playerNewtons = m_size.x *
                                m_size.y *
                                m_movementSpeedStraight;
    const float enemyNewtonsLimitedImproved = enemyNewtons * enemy->getPlayerMoveSlowDownRatio();
    const float enemyNewtonsLimited = enemyNewtonsLimitedImproved > playerNewtons ?
                                          playerNewtons : enemyNewtonsLimitedImproved;
    const float maxMoveLimit = 0.02;

    const float playerToEnemyRatioRaw = (playerNewtons - enemyNewtonsLimited) / playerNewtons;
    const float playerToEnemyRatioNormalized = playerToEnemyRatioRaw < maxMoveLimit ? maxMoveLimit : playerToEnemyRatioRaw;
    const float playerToEnemyRatioInverted = 1 - playerToEnemyRatioNormalized;
    const float playerToEnemyRatioRooted = sqrt(playerToEnemyRatioInverted);

    // if(p)
    //     printf("P: %0.2f, E: %0.2f, limit: %0.2f\n", playerNewtons, enemyNewtonsLimited, playerToEnemyRatioInverted);

    // if(p)
    //     fflush(stdout);

    /// test if collision occur
    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
    {
        /// test what collision is the smallest - that means this edges are colliding
        float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

        if (minOverlap == overlapLeft)
        {
            m_position.x -= m_moveVector.x * playerToEnemyRatioRooted;
        }
        else if (minOverlap == overlapRight)
        {
            m_position.x -= m_moveVector.x * playerToEnemyRatioRooted;
        }
        else if (minOverlap == overlapTop)
        {
            m_position.y -= m_moveVector.y * playerToEnemyRatioRooted;
        }
        else if (minOverlap == overlapBottom)
        {
            m_position.y -= m_moveVector.y * playerToEnemyRatioRooted;
        }
    }
}

// void Player::pollEvent(sf::Event &event)
// {

// }

void Player::limitPlayerMovementToMap()
{
    ///
    /// NOTE: move this logic to PlayState class
    ///

    FloatRectEdges playerEdges(
        m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    const sf::Vector2f &windowSize =
        GlobalData::getInstance()->getWindowSize();
    FloatRectEdges windowEgdes(0.f, 0.f, windowSize.x, windowSize.y);

    AdvancedComputation::preventMoveThatExitBounds(
        playerEdges, windowEgdes, m_size, m_position);

    for(Obstacle *obstacle : m_map->getObstacles())
        AdvancedComputation::preventMoveThatEnterBounds(
            playerEdges, obstacle->getBounds(), m_size, m_position);

    for(auto enemy : *m_enemies)
        this->limitMoveThatEnterEnemy(playerEdges, enemy);

}

void Player::updateBounds()
{
    m_bounds = sf::FloatRect(m_position, m_size);
}

void Player::updateCenter()
{
    m_center = sf::Vector2f(
        m_position.x + m_size.x/2,
        m_position.y + m_size.y/2);
}

void Player::updateRenderModel()
{
    if(m_boundsVisible)
        m_boundsShape.setPosition(m_position);

    m_renderModel.bounds.setPosition(m_center);
    m_renderModel.bounds.setRotation(m_rotationAngle);

    m_renderModel.skin.setPosition(m_center);
    m_renderModel.skin.setRotation(m_rotationAngle);

    m_renderModel.shirt.setPosition(m_center);
    m_renderModel.shirt.setRotation(m_rotationAngle);

    m_renderModel.bakpack.setPosition(m_center);
    m_renderModel.bakpack.setRotation(m_rotationAngle);
}

void Player::updateMovement()
{
    bool pressA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool pressW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool pressD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool pressS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    /// neutralize oposite forces
    if(pressA && pressD)
    {
        pressA = false;
        pressD = false;
    }
    if(pressW && pressS)
    {
        pressW = false;
        pressS = false;
    }

    const float straightSpeed = m_movementSpeedStraight;
    const float obliqueSpeed = m_movementSpeedOblique;

    if(pressA && pressW) this->move(-obliqueSpeed, -obliqueSpeed);        /// move left up
    else if(pressW && pressD) this->move(obliqueSpeed, -obliqueSpeed);    /// move right up
    else if(pressD && pressS) this->move(obliqueSpeed, obliqueSpeed);     /// move right down
    else if(pressS && pressA) this->move(-obliqueSpeed, obliqueSpeed);    /// move left down
    else if(pressA) this->move(-straightSpeed, 0.f);               /// move left
    else if(pressW) this->move(0.f, -straightSpeed);               /// move up
    else if(pressD) this->move(straightSpeed, 0.f);                /// mvoe down
    else if(pressS) this->move(0.f, straightSpeed);                /// move right
}

void Player::updateRotation()
{
    const sf::Vector2f &mousePos = GlobalData::getInstance()->getMousePosition();

    m_rotationAngle = AdvancedComputation::vectorToRotation(m_center, mousePos) +
                      PLAYER_ROTATION_ANGLE_CORRECTION;
}

void Player::updateWeapon()
{
    m_weapon->setPosition(m_position);
    m_weapon->setRotationAngle(m_rotationAngle);

    // static uint wi = 0; wi+=6;
    // if(wi >= 9*1000) wi = 0;
    // m_weapon->setWeaponIndex(wi/(1*1000));

    m_weapon->update();
}

void Player::updateArmor()
{
    // static uint hi = 0; hi+=3;
    // if(hi >= 6*1000) hi = 0;
    // m_armor->setHelmet(hi/(1*1000));

    // static uint ci = 0; ci+=5;
    // if(ci >= 6*1000) ci = 0;
    // m_armor->setChest(ci/(1*1000));

    // static uint ai = 0; ai+=7;
    // if(ai >= 6*1000) ai = 0;
    // m_armor->setArms(ai/(1*1000));

    // static uint fi = 0; fi+=11;
    // if(fi >= 6*1000) fi = 0;
    // m_armor->setForearms(fi/(1*1000));

    // static uint gi = 0; gi+=13;
    // if(gi >= 6*1000) gi = 0;
    // m_armor->setGloves(gi/(1*1000));

    m_armor->update();
}

void Player::updateEquipment()
{
    this->updateWeapon();
    this->updateArmor();
}

void Player::init()
{
    this->initData();
    this->deserializeData();
    this->initRenderModel();

    this->initEquipment();
}

void Player::pollEvent(const sf::Event &event)
{
    this->m_weapon->pollEvent(event);
    this->m_armor->pollEvent(event);
}

void Player::update()
{
    this->updateMovementSpeed();
    this->updateMovement();
    this->updateCenter();
    this->updateRotation();
    this->limitPlayerMovementToMap();

    this->updateBounds();
    this->updateRenderModel();

    this->updateEquipment();
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(m_renderModel.bounds);
    target->draw(m_renderModel.skin);
    target->draw(m_renderModel.shirt);
    target->draw(m_renderModel.bakpack);

    m_weapon->render(target);
    m_armor->render(target);

    if(m_boundsVisible)
        target->draw(m_boundsShape);
}

sf::Vector2f Player::getPosition() const
{
    return m_position;
}

const sf::FloatRect *Player::getBounds() const
{
    return &m_bounds;
}

Weapon *Player::getWeapon() const
{
    return m_weapon.get();
}

Armor *Player::getArmor() const
{
    return m_armor.get();
}

bool Player::getPlayerAlive() const
{
    return m_healthPoints > 0;
}

int Player::getHealthPoints() const
{
    return m_healthPoints;
}

void Player::setEnemies(const std::vector<std::shared_ptr<Enemy>> *enemies)
{
    m_enemies = enemies;
}

void Player::setPosition(const sf::Vector2f &position)
{
    m_position = sf::Vector2f(position.x - m_size.x/2, position.y - m_size.y/2);

    this->updateBounds();
    this->updateRenderModel();
}

void Player::setAvailableAreaForPlayer(std::shared_ptr<Map> map)
{
    m_map = map;
}

void Player::setWeapon(std::unique_ptr<Weapon> weapon)
{
    m_weapon.swap(weapon);
}

void Player::setArmor(std::unique_ptr<Armor> armor)
{
    m_armor.swap(armor);
}

void Player::dealDamage(float damage)
{
    float damageThatWasDecreasedByArmor =
        damage * (1.f-m_armor->getProtection());

    m_healthPoints -= damageThatWasDecreasedByArmor;
}

void Player::addMoney(float money)
{
    m_money += money;
}

void Player::resetHealtPoints()
{
    m_healthPoints = InitialData::Player::getHealthPoints();
}
