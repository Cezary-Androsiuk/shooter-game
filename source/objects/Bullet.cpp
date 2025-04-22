#include "Bullet.h"

#include "utils/Constants.h"
#include "utils/InitialData.h"
#include "utils/DeltaTime.h"
#include "utils/GlobalData.h"

void Bullet::initData()
{
    const float spriteScale = InitialData::getSpriteScale();
    m_size.x = MAIN_SPRITE::BULLET_FRAME_SIZE_X * spriteScale;
    m_size.y = MAIN_SPRITE::BULLET_FRAME_SIZE_Y * spriteScale;
    m_weaponIndex = 0;
    m_movementSpeed = InitialData::Bullet::getMovementSpeed();
    m_readyToDie = false;

}

void Bullet::initRenderModel()
{
    // m_renderModel.bounds.setPosition(m_position); /// position is (0,0)
    m_boundsShape.setFillColor(sf::Color::Transparent);
    m_boundsShape.setSize(m_size);
    m_boundsShape.setOutlineColor(InitialData::getBoundsColor());
    m_boundsShape.setOutlineThickness(InitialData::getBoundsThickness());
    m_boundsVisible = InitialData::Bullet::getShowBounds() || InitialData::getShowAllBounds();

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::BULLET_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::BULLET_FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::BULLET_FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::BULLET_FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int bulletYPos = frameOffsetY + frameSizeY * m_weaponIndex;
    m_renderModel.body.setTexture(mainSpriteTexture, false);
    m_renderModel.body.setTextureRect(
        sf::IntRect(frameOffsetX, bulletYPos, frameSizeX, frameSizeY));
    m_renderModel.body.setOrigin(frameSizeX/2, frameSizeY/2);
    m_renderModel.body.setScale(spriteScale, spriteScale);

    m_renderModel.simpleBody.setSize(sf::Vector2f(frameSizeX, frameSizeY));
    m_renderModel.simpleBody.setOrigin(frameSizeX/2, frameSizeY/2);
    m_renderModel.simpleBody.setScale(spriteScale, spriteScale);

}

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::updatePosition()
{
    const float dt = DeltaTime::get()->value();
    m_position.x += m_velocity.x * m_movementSpeed * dt;
    m_position.y += m_velocity.y * m_movementSpeed * dt;
}

void Bullet::updateRenderModel()
{
    m_boundsShape.setPosition(m_position);

    sf::Vector2f center(
        m_position.x + m_size.x/2,
        m_position.y + m_size.y/2);

    m_renderModel.body.setPosition(center);
    m_renderModel.simpleBody.setPosition(center);
}

void Bullet::updateReadyToDie()
{
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();
    const float margin = InitialData::Bullet::getAliveDistanceFromWindowEdge();

    bool crossedLeftEdge = m_position.x < 0.f - margin;
    bool crossedRightEdge = m_position.x > windowSize.x + margin;
    bool crossedTopEdge = m_position.y < 0.f - margin;
    bool crossedBottomEdge = m_position.y > windowSize.y + margin;

    if(crossedLeftEdge || crossedRightEdge || crossedTopEdge || crossedBottomEdge)
    {
        m_readyToDie = true;
    }

}

void Bullet::init()
{
    this->initData();
    this->initRenderModel();
}

void Bullet::pollEvent(const sf::Event &event)
{

}

void Bullet::update()
{
    this->updatePosition();
    this->updateReadyToDie();

    this->updateRenderModel();
}

void Bullet::render(sf::RenderTarget *target)
{
    target->draw(m_renderModel.body);
    target->draw(m_renderModel.simpleBody);

    if(m_boundsVisible)
        target->draw(m_boundsShape);
}

void Bullet::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Bullet::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Bullet::setWeaponIndex(uint index)
{
    m_weaponIndex = index;
}

void Bullet::setDamage(float damage)
{
    m_damage = damage;
}

bool Bullet::getReadyToDie()
{
    return m_readyToDie;
}
