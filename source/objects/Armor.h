#ifndef ARMOR_H
#define ARMOR_H

#include <SFML/Graphics.hpp>

class Armor
{
    void initData();

public:
    Armor();
    ~Armor();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

private:
};

#endif // ARMOR_H
