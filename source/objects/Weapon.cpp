#include "Weapon.h"

#include "utils/GlobalData.h"
#include "utils/InitialData.h"

void Weapon::initData()
{

}

void Weapon::initRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = 50;
    const int frameSizeY = 20;
    const float spriteScale = InitialData::getSpriteScale();

    m_renderModel.weaponBody.setTexture(mainSpriteTexture, false);
    m_renderModel.weaponBody.setTextureRect(sf::IntRect(240,0,frameSizeX,frameSizeY));
    m_renderModel.weaponBody.setOrigin(frameSizeX/2 ,frameSizeY/2); /// position is (0,0)
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
    m_renderModel.weaponBody.setPosition({100.f, 100.f});
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
