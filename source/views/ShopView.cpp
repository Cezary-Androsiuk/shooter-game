#include "ShopView.h"

#include "utils/GlobalData.h"
#include "utils/Constants.h"

void ShopView::initButtons()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    sf::Vector2f size(92,92);
    sf::Vector2f a(575, 320);
    float xoffset = 0;

    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_helmet[i] = std::make_unique<Button>();
        m_helmet[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_helmet[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_helmet[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_helmet[i]->setColor(sf::Color::Green);
        m_helmet[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_helmet[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }
    xoffset += size.x;

    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_chest[i] = std::make_unique<Button>();
        m_chest[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_chest[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_chest[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_chest[i]->setColor(sf::Color::Green);
        m_chest[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_chest[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }
    xoffset += size.x;

    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_arms[i] = std::make_unique<Button>();
        m_arms[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_arms[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_arms[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_arms[i]->setColor(sf::Color::Green);
        m_arms[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_arms[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }
    xoffset += size.x;

    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_forearms[i] = std::make_unique<Button>();
        m_forearms[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_forearms[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_forearms[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_forearms[i]->setColor(sf::Color::Green);
        m_forearms[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_forearms[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }
    xoffset += size.x;

    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_gloves[i] = std::make_unique<Button>();
        m_gloves[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_gloves[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_gloves[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_gloves[i]->setColor(sf::Color::Green);
        m_gloves[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_gloves[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }




    xoffset += size.x;
    size = sf::Vector2f(115,46);
    for(int i=0; i<WEAPON_TYPES_COUNT; i++)
    {
        float yoffset = size.y * i;
        m_weapons[i] = std::make_unique<Button>();
        m_weapons[i]->setPosition(sf::Vector2f((a.x + 641.f+5 + xoffset) *windowRatio.x, (a.y + 65.f+5 + yoffset) *windowRatio.y));
        m_weapons[i]->setSize(sf::Vector2f((size.x-10) *windowRatio.x, (size.y-10) *windowRatio.y));

        m_weapons[i]->setColor(ELEMENT_COLOR_IDLE);
        // m_weapons[i]->setColor(sf::Color::Green);
        m_weapons[i]->setColorHover(ELEMENT_COLOR_HOVER);
        m_weapons[i]->setColorPress(ELEMENT_COLOR_PRESS);
    }
}

ShopView::ShopView()
{

}

void ShopView::init()
{
    m_player = Player::getInstance();
    m_refreshSelectedDelay = 30;
    this->initButtons();

}

void ShopView::pollEvent(const sf::Event &event)
{
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_helmet[i]->event(event);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_chest[i]->event(event);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_arms[i]->event(event);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_forearms[i]->event(event);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_gloves[i]->event(event);

    for(int i=0; i<WEAPON_TYPES_COUNT; i++)
        m_weapons[i]->event(event);
}

void ShopView::update()
{
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        m_helmet[i]->update();
        if(m_helmet[i]->getClick())
        {
            m_player->getArmor()->setHelmet(i);
        }
    }
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        m_chest[i]->update();
        if(m_chest[i]->getClick())
        {
            m_player->getArmor()->setChest(i);
        }
    }
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        m_arms[i]->update();
        if(m_arms[i]->getClick())
        {
            m_player->getArmor()->setArms(i);
        }
    }
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        m_forearms[i]->update();
        if(m_forearms[i]->getClick())
        {
            m_player->getArmor()->setForearms(i);
        }
    }
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
    {
        m_gloves[i]->update();
        if(m_gloves[i]->getClick())
        {
            m_player->getArmor()->setGloves(i);
        }
    }


    for(int i=0; i<WEAPON_TYPES_COUNT; i++)
    {
        m_weapons[i]->update();
        if(m_weapons[i]->getClick())
        {
            m_player->getWeapon()->setWeaponIndex(i);
        }
    }

    if(m_refreshSelectedClock.getElapsedTime().asMilliseconds() > m_refreshSelectedDelay)
    {
        m_refreshSelectedClock.restart();


        int hi = m_player->getArmor()->getHelmetIndex();
        for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        {
            m_helmet[i]->setColor( hi == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );

        }


        int ci = m_player->getArmor()->getChestIndex();
        for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        {
            m_chest[i]->setColor( ci == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );
        }


        int ai = m_player->getArmor()->getArmsIndex();
        for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        {
            m_arms[i]->setColor( ai == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );
        }


        int fi = m_player->getArmor()->getForearmsIndex();
        for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        {
            m_forearms[i]->setColor( fi == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );
        }


        int gi = m_player->getArmor()->getGlovesIndex();
        for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        {
            m_gloves[i]->setColor( gi == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );
        }



        int wi = m_player->getWeapon()->getWeaponIndex();
        for(int i=0; i<WEAPON_TYPES_COUNT; i++)
        {
            m_weapons[i]->setColor( wi == i ? ELEMENT_COLOR_IDLE_SELECTED : ELEMENT_COLOR_IDLE );
        }
    }

}

void ShopView::render(sf::RenderTarget *target)
{
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_helmet[i]->render(target);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_chest[i]->render(target);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_arms[i]->render(target);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_forearms[i]->render(target);
    for(int i=0; i<ARMOR_TYPES_COUNT; i++)
        m_gloves[i]->render(target);

    for(int i=0; i<WEAPON_TYPES_COUNT; i++)
        m_weapons[i]->render(target);
}
