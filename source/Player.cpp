#include "Player.h"

void Player::initData()
{
    /// Position
    m_position.x = 0.f;
    m_position.y = 0.f;

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;
}

void Player::initBody()
{
    m_body.bounds.setPosition(m_position);
    m_body.bounds.setFillColor(sf::Color(180, 40, 40));
    m_body.bounds.setSize(m_size);
    m_body.bounds.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
}

Player::Player()
{
    this->initData();
    this->initBody();
}

Player::~Player()
{

}

void Player::updateBody()
{
    m_body.bounds.setPosition(m_position);
}

void Player::update()
{
    this->updateBody();
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(m_body.bounds);
}

void Player::setPosition(const sf::Vector2f &position)
{
    m_position = position;
}
