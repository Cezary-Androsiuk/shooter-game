#ifndef GOTDAMAGEANIMATION_H
#define GOTDAMAGEANIMATION_H

#include "animations/Animation.h"

class GotDamageAnimation : public Animation
{
    /* INITIALIZE */
    void initData();
    void initTexture();

public:
    GotDamageAnimation();
    ~GotDamageAnimation();

private:
    /* OTHER */

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void init() override;
    void pollEvent(const sf::Event &event) override;
    void update() override;
    void render(sf::RenderTarget *target) override;

    /* SETTERS */

private:
    sf::Clock m_decreaseIntensivityDelayClock;
    int m_decreaseIntensivityDelay;

};

#endif // GOTDAMAGEANIMATION_H
