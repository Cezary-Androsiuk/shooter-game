#include "Princess.h"

void Princess::initData()
{
    /// Position
    m_position.x = 0.f;
    m_position.y = 0.f;

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;
}

void Princess::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    m_body.bounds.setSize(m_size);
    m_body.bounds.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
}

Princess::Princess()
{
    this->initData();
    this->initBody();
}

Princess::~Princess()
{

}

void Princess::updateBody()
{
    m_body.bounds.setPosition(m_position);
}

void Princess::update()
{
    this->updateBody();
}

void Princess::render(sf::RenderTarget *target)
{
    target->draw(m_body.bounds);
}

void Princess::setPosition(const sf::Vector2f &position)
{
    m_position = position;
}
