#ifndef ARMOR_H
#define ARMOR_H

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"

class Armor
{
    void initData();

public:
    Armor();
    ~Armor();

private:
    /* OTHER */
    void setHelmetRenderModel();
    void setChestRenderModel();
    void setArmsRenderModel();
    void setForearmsRenderModel();
    void setGlovesRenderModel();

    void setHelmetProperties();
    void setChestProperties();
    void setArmsProperties();
    void setForearmsProperties();
    void setGlovesProperties();

    /* EVENTS */

    /* UPDATE */

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    /* GETTERS */
    float getProtection() const;

    /* SETTERS */
    void setPlayerPosition(const sf::Vector2f *position);
    void setPlayerSize(const sf::Vector2f *size);
    void setPlayerCenter(const sf::Vector2f *center);
    void setPlayerRotationAngle(const float *rotationAngle);

    void setHelmet(int helmetIndex);
    void setChest(int chestIndex);
    void setArms(int armsIndex);
    void setForearms(int forearmsIndex);
    void setGloves(int glovesIndex);

private:

    struct ArmorElement{
        std::unique_ptr<sf::Sprite> renderModel;
        uint elementIndex; /// describes type of helmet, type of glove etc.
        float protection;
    };

    ArmorElement m_helmet;
    ArmorElement m_chest;
    ArmorElement m_arms;
    ArmorElement m_forearms;
    ArmorElement m_gloves;

    const sf::Vector2f *m_playerPosition;
    const sf::Vector2f *m_playerSize;
    const sf::Vector2f *m_playerCenter;
    const float *m_playerRotationAngle;
};

#endif // ARMOR_H
