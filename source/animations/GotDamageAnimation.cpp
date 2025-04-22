#include "GotDamageAnimation.h"

#include "utils/GlobalData.h"

void GotDamageAnimation::initData()
{
    m_decreaseIntensivityDelay = 50;
}

void GotDamageAnimation::initTexture()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_sprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getGotDamageAnimationTexture(),
        sf::IntRect(0,0, 1920, 1080));
    m_sprite->setColor(sf::Color(255,255,255,200));
    m_sprite->setScale(windowRatio);
}

GotDamageAnimation::GotDamageAnimation()
    : Animation()
{
    this->init();
}

GotDamageAnimation::~GotDamageAnimation()
{

}

void GotDamageAnimation::init()
{
    this->initData();
    this->initTexture();
}

void GotDamageAnimation::pollEvent(const sf::Event &event)
{
    Animation::pollEvent(event);
}

void GotDamageAnimation::update()
{
    Animation::update();

    if(m_decreaseIntensivityDelayClock.
        getElapsedTime().asMilliseconds() > m_decreaseIntensivityDelay)
    {
        m_decreaseIntensivityDelayClock.restart();
        const sf::Color &color = m_sprite->getColor();
        m_sprite->setColor(sf::Color(color.r, color.g, color.b, color.a - 10));
    }

    if(m_sprite->getColor().a < 11)
        m_finished = true;
}

void GotDamageAnimation::render(sf::RenderTarget *target)
{
    Animation::render(target);

    target->draw(*m_sprite);
}
