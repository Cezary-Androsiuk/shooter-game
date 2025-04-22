#include "Armor.h"

#include "utils/InitialData.h"
#include "utils/GlobalData.h"

void Armor::initData()
{
    this->setHelmetProperties();
    this->setChestProperties();
    this->setArmsProperties();
    this->setForearmsProperties();
    this->setGlovesProperties();
}

void Armor::initRenderModels()
{
    this->setHelmetRenderModel();
    this->setChestRenderModel();
    this->setArmsRenderModel();
    this->setForearmsRenderModel();
    this->setGlovesRenderModel();
}

Armor::Armor()
    : m_playerCenter{nullptr}
    , m_playerRotationAngle{nullptr}
{
    m_helmet.elementIndex = 0;
    m_chest.elementIndex = 0;
    m_arms.elementIndex = 0;
    m_forearms.elementIndex = 0;
    m_gloves.elementIndex = 0;
}

Armor::~Armor()
{

}

void Armor::setHelmetRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ARMOR::HELMET::FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ARMOR::HELMET::FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ARMOR::HELMET::FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ARMOR::HELMET::FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int helmetYPos = frameOffsetY + frameSizeY * m_helmet.elementIndex;
    m_helmet.renderModel.setTexture(mainSpriteTexture, false);
    m_helmet.renderModel.setTextureRect(
        sf::IntRect(frameOffsetX, helmetYPos, frameSizeX, frameSizeY));
    m_helmet.renderModel.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_helmet.renderModel.setScale(spriteScale, spriteScale);
}

void Armor::setChestRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ARMOR::CHEST::FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ARMOR::CHEST::FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ARMOR::CHEST::FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ARMOR::CHEST::FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int chestYPos = frameOffsetY + frameSizeY * m_chest.elementIndex;
    m_chest.renderModel.setTexture(mainSpriteTexture, false);
    m_chest.renderModel.setTextureRect(
        sf::IntRect(frameOffsetX, chestYPos, frameSizeX, frameSizeY));
    m_chest.renderModel.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_chest.renderModel.setScale(spriteScale, spriteScale);
}

void Armor::setArmsRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ARMOR::ARMS::FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ARMOR::ARMS::FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ARMOR::ARMS::FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ARMOR::ARMS::FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int armsYPos = frameOffsetY + frameSizeY * m_arms.elementIndex;
    m_arms.renderModel.setTexture(mainSpriteTexture, false);
    m_arms.renderModel.setTextureRect(
        sf::IntRect(frameOffsetX, armsYPos, frameSizeX, frameSizeY));
    m_arms.renderModel.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_arms.renderModel.setScale(spriteScale, spriteScale);
}

void Armor::setForearmsRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ARMOR::FOREARMS::FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ARMOR::FOREARMS::FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ARMOR::FOREARMS::FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ARMOR::FOREARMS::FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int forearmsYPos = frameOffsetY + frameSizeY * m_forearms.elementIndex;
    m_forearms.renderModel.setTexture(mainSpriteTexture, false);
    m_forearms.renderModel.setTextureRect(
        sf::IntRect(frameOffsetX, forearmsYPos, frameSizeX, frameSizeY));
    m_forearms.renderModel.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_forearms.renderModel.setScale(spriteScale, spriteScale);
}

void Armor::setGlovesRenderModel()
{
    const sf::Texture &mainSpriteTexture =
        GlobalData::getInstance()->getMainSpriteTexture();

    const int frameSizeX = MAIN_SPRITE::ARMOR::GLOVES::FRAME_SIZE_X;
    const int frameSizeY = MAIN_SPRITE::ARMOR::GLOVES::FRAME_SIZE_Y;
    const int frameOffsetX = MAIN_SPRITE::ARMOR::GLOVES::FRAME_OFFSET_X;
    const int frameOffsetY = MAIN_SPRITE::ARMOR::GLOVES::FRAME_OFFSET_Y;
    const float spriteScale = InitialData::getSpriteScale();

    int glovesYPos = frameOffsetY + frameSizeY * m_gloves.elementIndex;
    m_gloves.renderModel.setTexture(mainSpriteTexture, false);
    m_gloves.renderModel.setTextureRect(
        sf::IntRect(frameOffsetX, glovesYPos, frameSizeX, frameSizeY));
    m_gloves.renderModel.setOrigin(frameSizeX/2 ,frameSizeY/2);
    m_gloves.renderModel.setScale(spriteScale, spriteScale);
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

void Armor::updateRenderModels()
{
    m_helmet.renderModel.setPosition(*m_playerCenter);
    m_helmet.renderModel.setRotation(*m_playerRotationAngle);

    m_chest.renderModel.setPosition(*m_playerCenter);
    m_chest.renderModel.setRotation(*m_playerRotationAngle);

    m_arms.renderModel.setPosition(*m_playerCenter);
    m_arms.renderModel.setRotation(*m_playerRotationAngle);

    m_forearms.renderModel.setPosition(*m_playerCenter);
    m_forearms.renderModel.setRotation(*m_playerRotationAngle);

    m_gloves.renderModel.setPosition(*m_playerCenter);
    m_gloves.renderModel.setRotation(*m_playerRotationAngle);
}

void Armor::init()
{
    this->initData();
    this->initRenderModels();
}

void Armor::pollEvent(const sf::Event &event)
{

}

void Armor::update()
{
    this->updateRenderModels();
}

void Armor::render(sf::RenderTarget *target)
{
    target->draw(m_helmet.renderModel);
    target->draw(m_chest.renderModel);
    target->draw(m_arms.renderModel);
    target->draw(m_forearms.renderModel);
    target->draw(m_gloves.renderModel);
}

float Armor::getProtection() const
{
    return m_helmet.protection +
           m_chest.protection +
           m_arms.protection +
           m_forearms.protection +
           m_gloves.protection;
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
    if(m_helmet.elementIndex == helmetIndex)
        return;

    if(helmetIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor helmet index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, helmetIndex);
        fflush(stderr);
        m_helmet.elementIndex = ARMOR_TYPES_COUNT-1;
    }
    else
    {
        m_helmet.elementIndex = helmetIndex;
    }

    this->setHelmetProperties();
    this->setHelmetRenderModel();
}

void Armor::setChest(int chestIndex)
{
    if(m_chest.elementIndex == chestIndex)
        return;

    if(chestIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor chest index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, chestIndex);
        fflush(stderr);
        m_chest.elementIndex = ARMOR_TYPES_COUNT-1;
    }
    else
    {
        m_chest.elementIndex = chestIndex;
    }

    this->setChestProperties();
    this->setChestRenderModel();
}

void Armor::setArms(int armsIndex)
{
    if(m_arms.elementIndex == armsIndex)
        return;

    if(armsIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor arms index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, armsIndex);
        fflush(stderr);
        m_arms.elementIndex = ARMOR_TYPES_COUNT-1;
    }
    else
    {
        m_arms.elementIndex = armsIndex;
    }

    this->setArmsProperties();
    this->setArmsRenderModel();
}

void Armor::setForearms(int forearmsIndex)
{
    if(m_forearms.elementIndex == forearmsIndex)
        return;

    if(forearmsIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor forearms index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, forearmsIndex);
        fflush(stderr);
        m_forearms.elementIndex = ARMOR_TYPES_COUNT-1;
    }
    else
    {
        m_forearms.elementIndex = forearmsIndex;
    }

    this->setForearmsProperties();
    this->setForearmsRenderModel();
}

void Armor::setGloves(int glovesIndex)
{
    if(m_gloves.elementIndex == glovesIndex)
        return;

    if(glovesIndex > ARMOR_TYPES_COUNT-1)
    {
        fprintf(stderr, "invalid armor gloves index, max is %u and got: %u. (using last instead)\n", ARMOR_TYPES_COUNT-1, glovesIndex);
        fflush(stderr);
        m_gloves.elementIndex = ARMOR_TYPES_COUNT-1;
    }
    else
    {
        m_gloves.elementIndex = glovesIndex;
    }

    this->setGlovesProperties();
    this->setGlovesRenderModel();
}
