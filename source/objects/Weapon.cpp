#include "Weapon.h"

#include "utils/GlobalData.h"
#include "utils/InitialData.h"

void Weapon::initData()
{
    m_setWeaponIndex = 0;
    m_shotDelay = InitialData::Weapon::getShotDelayMS();
    m_shotDelayTimer.restart();
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
    m_renderModel.weaponBody.setTextureRect(sf::IntRect(240, 0, frameSizeX, frameSizeY));
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
    if(m_setWeaponIndex != m_usedWeaponIndex)
    {
        const int frameSizeX = MAIN_SPRITE::WEAPON_FRAME_SIZE_X;
        const int frameSizeY = MAIN_SPRITE::WEAPON_FRAME_SIZE_Y;
        int weaponYPos = frameSizeY * m_setWeaponIndex;
        m_renderModel.weaponBody.setTextureRect(
            sf::IntRect(240, weaponYPos, frameSizeX, frameSizeY));
        m_usedWeaponIndex = m_setWeaponIndex;
    }

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

void Weapon::setWeaponIndex(uint index)
{
    if(index > 8)
    {
        fprintf(stderr, "invalid weapon index, max is 8 and got: %u. (using 8 instead)\n", index);
        fflush(stderr);
        m_setWeaponIndex = 8;
    }
    else
    {
        m_setWeaponIndex = index;
    }

}

std::unique_ptr<Bullet> Weapon::getBulletFromShot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(m_shotDelayTimer.getElapsedTime().asMilliseconds() > m_shotDelay)
        {
            static int i =0;
            m_shotDelayTimer.restart();
            printf("BANG %d %d   \n", i++, m_shotDelay);
            fflush(stdout);
        }
    }
    return nullptr;
}
