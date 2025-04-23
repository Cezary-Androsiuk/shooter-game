#ifndef ARMOR_H
#define ARMOR_H

#include <SFML/Graphics.hpp>

#include "utils/Constants.h"

class Armor
{
    void initData();
    void initRenderModels();

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
    void updateRenderModels();

    /* RENDER */

public:
    void init();
    void pollEvent(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *target);

    /* GETTERS */
    float getProtection() const;
    int getHelmetIndex() const;
    int getChestIndex() const;
    int getArmsIndex() const;
    int getForearmsIndex() const;
    int getGlovesIndex() const;

    /* SETTERS */
    void setPlayerCenter(const sf::Vector2f *center);
    void setPlayerRotationAngle(const float *rotationAngle);

    void setHelmet(int helmetIndex);
    void setChest(int chestIndex);
    void setArms(int armsIndex);
    void setForearms(int forearmsIndex);
    void setGloves(int glovesIndex);

private:

    struct ArmorElement{
        sf::Sprite renderModel;
        uint elementIndex; /// describes type of helmet, type of glove etc.
        float protection;
    };

    ArmorElement m_helmet;
    ArmorElement m_chest;
    ArmorElement m_arms;
    ArmorElement m_forearms;
    ArmorElement m_gloves;

    const sf::Vector2f *m_playerCenter;
    const float *m_playerRotationAngle;
};

#endif // ARMOR_H
