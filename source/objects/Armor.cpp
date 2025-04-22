#include "Armor.h"

#include "utils/InitialData.h"
#include "utils/GlobalData.h"

void Armor::initData()
{

}

Armor::Armor()
    : m_playerPosition{nullptr}
    , m_playerSize{nullptr}
    , m_playerCenter{nullptr}
    , m_playerRotationAngle{nullptr}
{

}

Armor::~Armor()
{

}

void Armor::setHelmetRenderModel()
{

}

void Armor::setChestRenderModel()
{

}

void Armor::setArmsRenderModel()
{

}

void Armor::setForearmsRenderModel()
{

}

void Armor::setGlovesRenderModel()
{

}

void Armor::setHelmetProperties()
{
    m_helmet.protection =
        InitialData::Armor::getHelemtProtection(m_helmet.elementIndex);
}

void Armor::setChestProperties()
{
    m_chest.protection =
        InitialData::Armor::getChestProtection(m_chest.elementIndex);
}

void Armor::setArmsProperties()
{
    m_arms.protection =
        InitialData::Armor::getArmsProtection(m_arms.elementIndex);
}

void Armor::setForearmsProperties()
{
    m_forearms.protection =
        InitialData::Armor::getForearmsProtection(m_forearms.elementIndex);
}

void Armor::setGlovesProperties()
{
    m_gloves.protection =
        InitialData::Armor::getGlovesProtection(m_gloves.elementIndex);
}

void Armor::init()
{
    this->initData();
}

void Armor::pollEvent(const sf::Event &event)
{

}

void Armor::update()
{

}

void Armor::render(sf::RenderTarget *target)
{

}

float Armor::getProtection() const
{
    return m_helmet.protection +
           m_chest.protection +
           m_arms.protection +
           m_forearms.protection +
           m_gloves.protection;
}

void Armor::setPlayerPosition(const sf::Vector2f *position)
{
    m_playerPosition = position;
}

void Armor::setPlayerSize(const sf::Vector2f *size)
{
    m_playerSize = size;
}

void Armor::setPlayerCenter(const sf::Vector2f *center)
{
    m_playerCenter = center;
}

void Armor::setPlayerRotationAngle(const float *rotationAngle)
{
    m_playerRotationAngle = rotationAngle;
}

void Armor::setHelmet(int helmetIndex)
{

}

void Armor::setChest(int chestIndex)
{

}

void Armor::setArms(int armsIndex)
{

}

void Armor::setForearms(int forearmsIndex)
{

}

void Armor::setGloves(int glovesIndex)
{

}
