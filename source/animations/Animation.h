#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

#include <memory>

class Animation
{
    /* INITIALIZE */
    void initData();

public:
    Animation();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    virtual void init();
    virtual void pollEvent(const sf::Event &event);
    virtual void update();
    virtual void render(sf::RenderTarget *target);

    /* GETTERS */
    bool getFinished() const;

    /* SETTERS */

protected:
    std::unique_ptr<sf::Sprite> m_sprite;

    bool m_finished;
};

#endif // ANIMATION_H
