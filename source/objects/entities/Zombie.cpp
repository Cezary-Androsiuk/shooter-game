#include "Zombie.h"

#include "utils/InitialData.h"
#include "utils/GlobalData.h"

void Zombie::initData()
{
    if(m_type > ZOMBIE_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid enemy type, max is %u and got: %u. (using last instead)\n", ZOMBIE_TYPES_COUNT-1, m_type);
        fflush(stderr);
        m_type = ZOMBIE_TYPES_COUNT-1;
    }

    m_movementSpeedAddons.msDefault = InitialData::Enemy::Zombie::getMovementSpeed(m_type);
    m_playerMoveSlowDownRatio = InitialData::Enemy::Zombie::getPlayerMoveSlowDownRatio(m_type);
    m_healthPoints = InitialData::Enemy::Zombie::getHealthPoints(m_type);
    m_damage = InitialData::Enemy::Zombie::getDamage(m_type);

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;

    m_netWorth = Random::getFloat(
                     InitialData::Enemy::getMoneyDecreaseRandomness(),
                     InitialData::Enemy::getMoneyIncreaseRandomness()
                     ) * InitialData::Enemy::Zombie::getNetWorth(m_type);
    m_netWorth = round(m_netWorth * 100) / 100.f;
}

void Zombie::initRenderModel()
{
    m_boundsShape.setFillColor(sf::Color::Transparent);
    m_boundsShape.setSize(m_size);
    m_boundsShape.setOutlineColor(InitialData::getBoundsColor());
    m_boundsShape.setOutlineThickness(InitialData::getBoundsThickness());
    m_boundsVisible = InitialData::Enemy::getShowBounds() || InitialData::getShowAllBounds();

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ENEMY_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ENEMY_FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ENEMY_FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ENEMY_FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int enemyYPos = frameOffsetY + frameSizeY * m_type;
    m_renderModel.body.setTexture(mainSpriteTexture, false);
    m_renderModel.body.setTextureRect(
        sf::IntRect(frameOffsetX, enemyYPos, frameSizeX, frameSizeY));
    m_renderModel.body.setOrigin(frameSizeX/2, frameSizeY/2);
    m_renderModel.body.setScale(spriteScale, spriteScale);
}

Zombie::Zombie(uint type)
    : Enemy()
    , m_type{type}
{

}

Zombie::~Zombie()
{

}

void Zombie::limitZombieMovementToMap()
{
    ///
    /// NOTE: move this logic to PlayState class
    ///

    FloatRectEdges entityEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    FloatRectEdges playerBounds(
        m_playerBounds->left, m_playerBounds->top,
        m_playerBounds->left + m_playerBounds->width, m_playerBounds->top + m_playerBounds->height);

    this->preventMoveThatEnterBounds(entityEdges, playerBounds);

    for(Obstacle *obstacle : m_map->getObstacles())
        this->preventMoveThatEnterBounds(entityEdges, obstacle->getBounds());
}

void Zombie::updateRenderModel()
{
    if(m_boundsVisible)
        m_boundsShape.setPosition(m_position);

    sf::Vector2f center(
        m_position.x + m_size.x/2,
        m_position.y + m_size.y/2);

    m_renderModel.body.setPosition(center);
    m_renderModel.body.setRotation(m_rotationAngle);
}


void Zombie::init()
{
    Enemy::init();

    this->initData();
    this->initRenderModel();
}

void Zombie::pollEvent(const sf::Event &event)
{
    Enemy::pollEvent(event);
}

void Zombie::update()
{
    Enemy::update();

    this->limitZombieMovementToMap();

    this->updateRenderModel();
}

void Zombie::render(sf::RenderTarget *target)
{
    Enemy::render(target);

    target->draw(m_renderModel.body);

    if(m_boundsVisible)
        target->draw(m_boundsShape);
}
