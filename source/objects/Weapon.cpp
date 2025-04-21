#include "Weapon.h"

#include "utils/Constants.h"
#include "utils/GlobalData.h"
#include "utils/InitialData.h"

void Weapon::initData()
{

}

void Weapon::initRenderModel()
{
    /// weapon does not have bounds

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::WEAPON_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::WEAPON_FRAME_SIZE_Y;
    const float spriteScale = InitialData::getSpriteScale();

    m_renderModel.weaponBody.setTexture(mainSpriteTexture, false);
    m_renderModel.weaponBody.setTextureRect(sf::IntRect(240,frameSizeY*1,frameSizeX,frameSizeY));
    m_renderModel.weaponBody.setOrigin(16, 6); /// position is (0,0)
    m_renderModel.weaponBody.setScale(spriteScale, spriteScale);
}

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

void Weapon::updateRenderModel()
{
    m_renderModel.weaponBody.setPosition(sf::Vector2f(
        m_position.x + m_playerSize.x/2,
        m_position.y + m_playerSize.y/2));
    m_renderModel.weaponBody.setRotation(m_rotationAngle);
}

void Weapon::init()
{
    this->initData();
    this->initRenderModel();
}

void Weapon::pollEvent(const sf::Event &event)
{

}

void Weapon::update()
{

    this->updateRenderModel();
}

void Weapon::render(sf::RenderTarget *target)
{
    target->draw(m_renderModel.weaponBody);
}

void Weapon::setPlayerSize(sf::Vector2f playerSize)
{
    m_playerSize = playerSize;
}

void Weapon::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Weapon::setRotationAngle(float rotationAngle)
{
    m_rotationAngle = rotationAngle;
}
