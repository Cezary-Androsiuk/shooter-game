#include "Player.h"

void Player::initData()
{
    /// Position
    m_position.x = 0.f;
    m_position.y = 0.f;

    /// Size
    m_size.x = 50.f;
    m_size.y = 50.f;

    m_points = 0;
    m_healthPoints = PLAYER_HP;
    m_ammo = PLAYER_AMMO;
    m_headCount = 0;
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

void Player::move(float xmove, float ymove)
{
    m_position = sf::Vector2f(
        m_position.x + xmove,
        m_position.y + ymove
    );
}

void Player::move(sf::Vector2f move)
{
    m_position = sf::Vector2f(
        m_position.x + move.x,
        m_position.y + move.y
    );
}

// void Player::pollEvent(sf::Event &event)
// {

// }

void Player::limitPlayerMovementToScreenArea()
{
    sf::Vector2f leftCornerPosition(m_position.x - m_size.x/2, m_position.y = m_size.y/2);
    sf::FloatRect playerBounds(leftCornerPosition, m_size);

    /// Left
    if(playerBounds.left <= m_availableAreaForPlayer.left)
        m_position = sf::Vector2f(
            m_availableAreaForPlayer.left,
            m_position.y);
    /// Right
    if(playerBounds.left + playerBounds.width >= m_availableAreaForPlayer.left + m_availableAreaForPlayer.width)
        m_position = sf::Vector2f(
            m_availableAreaForPlayer.left + m_availableAreaForPlayer.width - playerBounds.width,
            m_position.y);
    /// Top
    if(playerBounds.top <= m_availableAreaForPlayer.top)
        m_position = sf::Vector2f(
            m_position.x,
            m_availableAreaForPlayer.top);
    /// Bottom
    if(playerBounds.top + playerBounds.height >= m_availableAreaForPlayer.top + m_availableAreaForPlayer.height)
        m_position = sf::Vector2f(
            m_position.x,
            m_availableAreaForPlayer.top + m_availableAreaForPlayer.height - playerBounds.height);
}

void Player::updateBody()
{
    m_body.bounds.setPosition(m_position);
}

void Player::updateMovement()
{
    const float pss = PLAYER_SPEED_STRAIGHT * DeltaTime::get()->value();
    const float pso = PLAYER_SPEED_OBLIQUE * DeltaTime::get()->value();

    const bool pressA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    const bool pressW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    const bool pressD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    const bool pressS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    if(pressA && pressW) this->move(-pso, -pso);        /// move left up
    else if(pressW && pressD) this->move(pso, -pso);    /// move right up
    else if(pressD && pressS) this->move(pso, pso);     /// move right down
    else if(pressS && pressA) this->move(-pso, pso);    /// move left down
    else if(pressA) this->move(-pss,0.f);               /// move left
    else if(pressW) this->move(0.f,-pss);               /// move up
    else if(pressD) this->move(pss,0.f);                /// mvoe down
    else if(pressS) this->move(0.f,pss);                /// move right
}

void Player::update()
{

    this->updateMovement();
    // this->limitPlayerMovementToScreenArea();

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

void Player::setAvailableAreaForPlayer(const sf::FloatRect availableAreaForPlayer)
{
    m_availableAreaForPlayer = availableAreaForPlayer;
}
