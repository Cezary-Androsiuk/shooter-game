#include "Player.h"

#include "utils/InitialData.h"
#include "utils/DeltaTime.h"
#include "utils/GlobalData.h"

void Player::initData()
{
    /// Position
    m_position.x = 0.f;
    m_position.y = 0.f;

    /// Size
    m_size.x = 70.f;
    m_size.y = 70.f;

    m_points = 0;
    m_healthPoints = InitialData::Player::getHealthPoints();
    m_ammo = InitialData::Player::getAmmo();
    m_headCount = 0;

    m_movementSpeedAddons.msStraightDefault = InitialData::Player::getSpeedStraight();
    m_movementSpeedAddons.msMultiplier = 1.0;
}

void Player::initBody()
{
    // m_body.bounds.setPosition(m_position); /// position is (0,0)
    // m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    // m_body.bounds.setSize(m_size);

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSize = 40;
    const float spriteScale = 1.68;

    m_body.bodyBounds.setTexture(mainSpriteTexture, false);
    m_body.bodyBounds.setTextureRect(sf::IntRect(0,0,frameSize,frameSize));
    m_body.bodyBounds.setOrigin(frameSize/2 ,frameSize/2); /// position is (0,0)
    m_body.bodyBounds.setScale(spriteScale, spriteScale);


    m_body.bodySkin.setTexture(mainSpriteTexture, false);
    m_body.bodySkin.setTextureRect(sf::IntRect(0,frameSize,frameSize,frameSize));
    m_body.bodySkin.setOrigin(frameSize/2 ,frameSize/2); /// position is (0,0)
    m_body.bodySkin.setScale(spriteScale, spriteScale);


    m_body.bodyShirt.setTexture(mainSpriteTexture, false);
    m_body.bodyShirt.setTextureRect(sf::IntRect(0,frameSize*2,frameSize,frameSize));
    m_body.bodyShirt.setOrigin(frameSize/2 ,frameSize/2); /// position is (0,0)
    m_body.bodyShirt.setScale(spriteScale, spriteScale);
    // auto c = m_body.bodyShirt.getColor();
    // printf("getColor: %u, %u, %u, %u\n", c.r, c.g, c.b, c.a);
    m_body.bodyShirt.setColor(sf::Color(255, 0, 0, 255));


    m_body.bodyBakpack.setTexture(mainSpriteTexture, false);
    m_body.bodyBakpack.setTextureRect(sf::IntRect(0,frameSize*3,frameSize,frameSize));
    m_body.bodyBakpack.setOrigin(frameSize/2 ,frameSize/2); /// position is (0,0)
    m_body.bodyBakpack.setScale(spriteScale, spriteScale);

}

Player::Player()
{
    this->initData();
    this->initBody();
}

Player::~Player()
{

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

void Player::computeMovementSpeed()
{
    m_movementSpeedStraight = m_movementSpeedAddons.msStraightDefault *
                              m_movementSpeedAddons.msMultiplier *
                              DeltaTime::get()->value();
    m_movementSpeedOblique = m_movementSpeedStraight / 1.4142f /* sqrt(2) */;
}

float Player::rotationFromVector(cvFloat originPoint, cvFloat targetPoint)
{
    /// compute difference
    float dx = targetPoint.x - originPoint.x;
    float dy = targetPoint.y - originPoint.y;

    /// compute angle in radians (knowing that axis Y is inverted in SFML)
    float angleRadians = std::atan2(-dy, dx);
    // printf("Angle: %.2f  |   Pos: %.2f, %.2f   |   ", angleRadians, dx, dy);

    /// convert radians to degrees
    float angleDegrees = angleRadians * (180.0f / static_cast<float>(M_PI));
    angleDegrees = -angleDegrees;

    /// normalize angle [0, 360)
    if (angleDegrees < 0) {
        angleDegrees += 360.0f;
    }

    return angleDegrees;
}

void Player::preventMoveThatExitBounds(const FloatRectEdges &playerBounds, const FloatRectEdges &obstacleBounds)
{
    /// Left
    if(playerBounds.left <= obstacleBounds.left)
        m_position = sf::Vector2f(
            obstacleBounds.left,
            m_position.y);
    /// Right
    if(playerBounds.right >= obstacleBounds.right)
        m_position = sf::Vector2f(
            obstacleBounds.right - m_size.x,
            m_position.y);
    /// Top
    if(playerBounds.top <= obstacleBounds.top)
        m_position = sf::Vector2f(
            m_position.x,
            obstacleBounds.top);
    /// Bottom
    if(playerBounds.bottom >= obstacleBounds.bottom)
        m_position = sf::Vector2f(
            m_position.x,
            obstacleBounds.bottom - m_size.y);
}

void Player::preventMoveThatEnterBounds(
    const FloatRectEdges &playerBounds,
    const FloatRectEdges &obstacleBounds)
{
    float overlapLeft   = playerBounds.right - obstacleBounds.left;
    float overlapRight  = obstacleBounds.right - playerBounds.left;
    float overlapTop    = playerBounds.bottom - obstacleBounds.top;
    float overlapBottom = obstacleBounds.bottom - playerBounds.top;

    /// test if collision occur
    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0)
    {
        /// test what collision is the smallest - that means this edges are colliding
        float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

        if (minOverlap == overlapLeft)
        {
            m_position.x = obstacleBounds.left - m_size.x;
        }
        else if (minOverlap == overlapRight)
        {
            m_position.x = obstacleBounds.right;
        }
        else if (minOverlap == overlapTop)
        {
            m_position.y = obstacleBounds.top - m_size.y;
        }
        else if (minOverlap == overlapBottom)
        {
            m_position.y = obstacleBounds.bottom;
        }
    }
}

void Player::limitMoveThatEnterEnemy(
    const FloatRectEdges &playerBounds, std::shared_ptr<Enemy> enemy)
{
    const FloatRectEdges enemyBounds(enemy->getBounds());

    const float overlapLeft   = playerBounds.right - enemyBounds.left;
    const float overlapRight  = enemyBounds.right - playerBounds.left;
    const float overlapTop    = playerBounds.bottom - enemyBounds.top;
    const float overlapBottom = enemyBounds.bottom - playerBounds.top;

    // bool p = DeltaTime::canPrint();

    const float dt = DeltaTime::get()->value();
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
    FloatRectEdges playerEdges(
        m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    const sf::Vector2f &windowSize =
        GlobalData::getInstance()->getWindowSize();
    FloatRectEdges windowEgdes(0.f, 0.f, windowSize.x, windowSize.y);

    this->preventMoveThatExitBounds(playerEdges, windowEgdes);

    for(Obstacle *obstacle : m_map->getObstacles())
        this->preventMoveThatEnterBounds(playerEdges, obstacle->getBounds());

    for(auto enemy : *m_enemies)
        this->limitMoveThatEnterEnemy(playerEdges, enemy);

}

void Player::updateBody()
{
    // m_body.bounds.setPosition(m_position);

    sf::Vector2f centerPoint(
        m_position.x + m_size.x/2,
        m_position.y + m_size.y/2);

    m_body.bodyBounds.setPosition(centerPoint);
    m_body.bodyBounds.setRotation(m_rotationAngle);

    m_body.bodySkin.setPosition(centerPoint);
    m_body.bodySkin.setRotation(m_rotationAngle);

    m_body.bodyShirt.setPosition(centerPoint);
    m_body.bodyShirt.setRotation(m_rotationAngle);

    m_body.bodyBakpack.setPosition(centerPoint);
    m_body.bodyBakpack.setRotation(m_rotationAngle);
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

    m_rotationAngle = Player::rotationFromVector(
        {
            m_position.x + m_size.x/2,
            m_position.y + m_size.y/2
        },
        mousePos
        );

    if(DeltaTime::canPrint())
    {

        // printf("Angle: %.2f  |   Pos: %.2f, %.2f\n", angle, mousePos.x, mousePos.y);
        // fflush(stdout);
    }

}

void Player::updateBounds()
{
    m_bounds = sf::FloatRect(m_position, m_size);
}

void Player::update()
{
    this->computeMovementSpeed();
    this->updateMovement();
    this->updateRotation();
    this->limitPlayerMovementToMap();

    this->updateBounds();
    this->updateBody();
}

void Player::render(sf::RenderTarget *target)
{
    // target->draw(m_body.bounds);

    target->draw(m_body.bodyBounds);
    target->draw(m_body.bodySkin);
    target->draw(m_body.bodyShirt);
    target->draw(m_body.bodyBakpack);
}

sf::Vector2f Player::getPosition() const
{
    return m_position;
}

const sf::FloatRect *Player::getBounds() const
{
    return &m_bounds;
}

void Player::setEnemies(const std::vector<std::shared_ptr<Enemy>> *enemies)
{
    m_enemies = enemies;
}

void Player::setPosition(const sf::Vector2f &position)
{
    m_position = sf::Vector2f(position.x - m_size.x/2, position.y - m_size.y/2);

    this->updateBounds();
    this->updateBody();
}

void Player::setAvailableAreaForPlayer(std::shared_ptr<Map> map)
{
    m_map = map;
}
