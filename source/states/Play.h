#ifndef PLAY_H
#define PLAY_H

#include <SFML/Graphics.hpp>

#include "State.h"

#include "objects/entities/Player.h"
#include "environment/Map.h"

class Play : public State
{
    void initMap();
    void initPlayer();
    void initObjects();

public:
    Play();
    ~Play();

    void init();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /// SETTERS
    void setWindowSize(const sf::Vector2u &size);

private:
    sf::Vector2u m_windowSize;

    std::shared_ptr<Map> m_map;
    Player m_player;
};

#endif // PLAY_H
