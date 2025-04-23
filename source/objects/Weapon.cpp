#include "Weapon.h"

#include "utils/GlobalData.h"
#include "utils/InitialData.h"
#include "utils/Support.h"
#include "utils/AdvancedComputation.h"
#include "environment/Sound.h"

void Weapon::initData()
{

    m_shotDelay = InitialData::Weapon::getShotDelayMS(m_usedWeaponIndex);
    m_shotDelayTimer.restart();

    this->rememberIfMouseButtonClicked();
    m_clickCorrection.needCheck = true;
}

void Weapon::initRenderModel()
{
    /// weapon does not have bounds

    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::WEAPON_FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::WEAPON_FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::WEAPON_FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::WEAPON_FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    m_renderModel.body.setTexture(mainSpriteTexture, false);
    m_renderModel.body.setTextureRect(
        sf::IntRect(frameOffsetX, frameOffsetY, frameSizeX, frameSizeY));
    m_renderModel.body.setOrigin(16, 6);
    m_renderModel.body.setScale(spriteScale, spriteScale);
}

Weapon::Weapon()
{
    m_setWeaponIndex = 0;
}

Weapon::~Weapon()
{

}

void Weapon::updateWeaponType()
{
    if(m_setWeaponIndex != m_usedWeaponIndex)
    {
        const int frameSizeX = MAIN_SPRITE::WEAPON_FRAME_SIZE_X;
        const int frameSizeY = MAIN_SPRITE::WEAPON_FRAME_SIZE_Y;
        const int frameOffsetX = MAIN_SPRITE::WEAPON_FRAME_OFFSET_X;
        const int frameOffsetY = MAIN_SPRITE::WEAPON_FRAME_OFFSET_Y;

        int weaponYPos = frameOffsetY + frameSizeY * m_setWeaponIndex;
        m_renderModel.body.setTextureRect(
            sf::IntRect(frameOffsetX, weaponYPos, frameSizeX, frameSizeY));
        m_usedWeaponIndex = m_setWeaponIndex;

        m_shotDelay = InitialData::Weapon::getShotDelayMS(m_usedWeaponIndex);
    }
}

void Weapon::updateRenderModel()
{
    m_renderModel.body.setPosition(sf::Vector2f(
        m_position.x + m_playerSize.x/2,
        m_position.y + m_playerSize.y/2));
    m_renderModel.body.setRotation(m_rotationAngle);
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
    this->updateWeaponType();

    this->updateRenderModel();
}

void Weapon::render(sf::RenderTarget *target)
{
    target->draw(m_renderModel.body);
}

std::unique_ptr<Bullet> Weapon::getBulletFromShot()
{
    if(UNLIKELY(m_clickCorrection.needCheck))
    {
        if(m_clickCorrection.mouseLButtonClickedWhileInitialization)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                /// prevent creating new bullets if while creating
                /// weapon left mouse button is pressed
                return nullptr;
            }
            else
            {
                m_clickCorrection.needCheck = false;
            }
        }
        else
        {
            m_clickCorrection.needCheck = false;
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(m_shotDelayTimer.getElapsedTime().asMilliseconds() > m_shotDelay)
        {
            m_shotDelayTimer.restart();

            Sound::getInstance()->playShot();

            std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>();

            sf::Vector2f playerCenter(
                m_position.x + m_playerSize.x/2,
                m_position.y + m_playerSize.y/2);

            sf::Vector2f bulletStartPosition =
                AdvancedComputation::rotatePointAroundOrigin(
                    sf::Vector2f(
                        playerCenter.x,
                        playerCenter.y + 6.f),
                    playerCenter,
                    m_rotationAngle);

            bullet->setPosition(bulletStartPosition);
            bullet->setVelocity(AdvancedComputation::rotationToVector(m_rotationAngle));
            bullet->setWeaponIndex(m_usedWeaponIndex);
            bullet->setDamage(InitialData::Weapon::getDamage(m_usedWeaponIndex));

            bullet->init();

            return bullet;
        }
    }
    return nullptr;
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
    if(index > WEAPON_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid weapon index, max is %u and got: %u. (using last instead)\n", WEAPON_TYPES_COUNT-1, index);
        fflush(stderr);
        m_setWeaponIndex = WEAPON_TYPES_COUNT-1;
    }
    else
    {
        m_setWeaponIndex = index;
    }
}

void Weapon::rememberIfMouseButtonClicked()
{
    m_clickCorrection.mouseLButtonClickedWhileInitialization =
        sf::Mouse::isButtonPressed(sf::Mouse::Left);
    m_clickCorrection.needCheck = true;
}
