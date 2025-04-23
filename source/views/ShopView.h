#ifndef SHOPVIEW_H
#define SHOPVIEW_H
#include <SFML/Graphics.hpp>
#include <SimpleGUI/Button.hpp>

#include <memory>

#include "objects/entities/Player.h"

using namespace sgui;

class ShopView
{
    void initButtons();

public:
    ShopView();

    void init();

public:
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

private:
    Player *m_player;

    std::unique_ptr<Button> m_helmet[ARMOR_TYPES_COUNT];
    std::unique_ptr<Button> m_chest[ARMOR_TYPES_COUNT];
    std::unique_ptr<Button> m_arms[ARMOR_TYPES_COUNT];
    std::unique_ptr<Button> m_forearms[ARMOR_TYPES_COUNT];
    std::unique_ptr<Button> m_gloves[ARMOR_TYPES_COUNT];

    std::unique_ptr<Button> m_weapons[WEAPON_TYPES_COUNT];
};

#endif // SHOPVIEW_H
