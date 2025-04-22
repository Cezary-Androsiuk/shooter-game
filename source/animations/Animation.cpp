#include "Animation.h"

void Animation::initData()
{

}

Animation::Animation()
    : m_finished{false}
{
    this->init();
}

void Animation::init()
{
    this->initData();
}

void Animation::pollEvent(const sf::Event &event)
{

}

void Animation::update()
{

}

void Animation::render(sf::RenderTarget *target)
{

}

bool Animation::getFinished() const
{
    return m_finished;
}
