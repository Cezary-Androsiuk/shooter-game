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
    // m_body.bounds.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
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

void Player::preventMoveThatExitBounds(const FloatRectEdges &playerBounds, const FloatRectEdges &obstacleBounds)
{
    /// Left
    if(playerBounds.left <= obstacleBounds.left)
        m_position = sf::Vector2f(
            obstacleBounds.left,
            m_position.y);
    /// Right
    if(playerBounds.right >= obstacleBounds.right)
        m_position = sf::Vector2f(
            obstacleBounds.right - m_size.x,
            m_position.y);
    /// Top
    if(playerBounds.top <= obstacleBounds.top)
        m_position = sf::Vector2f(
            m_position.x,
            obstacleBounds.top);
    /// Bottom
    if(playerBounds.bottom >= obstacleBounds.bottom)
        m_position = sf::Vector2f(
            m_position.x,
            obstacleBounds.bottom - m_size.y);
}

void Player::preventMoveThatEnterBounds(
    const FloatRectEdges &playerBounds,
    const FloatRectEdges &obstacleBounds)
{
    /// Left
    if(playerBounds.right >= obstacleBounds.left &&
        playerBounds.left < obstacleBounds.left &&
        playerBounds.bottom > obstacleBounds.top &&
        playerBounds.top < obstacleBounds.bottom)
    {
        m_position.x = obstacleBounds.left - m_size.x;
    }
    /// Right
    else if(playerBounds.left <= obstacleBounds.right &&
             playerBounds.right > obstacleBounds.right &&
             playerBounds.bottom > obstacleBounds.top &&
             playerBounds.top < obstacleBounds.bottom)
    {
        m_position.x = obstacleBounds.right;
    }
    /// Top
    else if(playerBounds.bottom >= obstacleBounds.top &&
             playerBounds.top < obstacleBounds.top &&
             playerBounds.right > obstacleBounds.left &&
             playerBounds.left < obstacleBounds.right)
    {
        m_position.y = obstacleBounds.top - m_size.y;
    }
    /// Bottom
    else if(playerBounds.top <= obstacleBounds.bottom &&
             playerBounds.bottom > obstacleBounds.bottom &&
             playerBounds.right > obstacleBounds.left &&
             playerBounds.left < obstacleBounds.right)
    {
        m_position.y = obstacleBounds.bottom;
    }
}

// void Player::pollEvent(sf::Event &event)
// {

// }

void Player::limitPlayerMovementToScreenArea()
{
    FloatRectEdges playerEdges(m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y);
    float windowSizeX = static_cast<float>(m_map->getMapSize().x);
    float windowSizeY = static_cast<float>(m_map->getMapSize().y);
    FloatRectEdges windowEgdes(0.f, 0.f, windowSizeX, windowSizeY);

    this->preventMoveThatExitBounds(playerEdges, windowEgdes);

    for(Obstacle *obstacle : m_map->getObstacles())
        this->preventMoveThatEnterBounds(playerEdges, obstacle->getBounds());
}

void Player::updateBody()
{
    m_body.bounds.setPosition(m_position);
}

void Player::updateMovement()
{
    const float pss = PLAYER_SPEED_STRAIGHT * DeltaTime::get()->value();
    const float pso = PLAYER_SPEED_OBLIQUE * DeltaTime::get()->value();

    bool pressA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool pressW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool pressD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool pressS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    /// neutralize oposite forces
    if(pressA && pressD)
    {
        pressA = false;
        pressD = false;
    }
    if(pressW && pressS)
    {
        pressW = false;
        pressS = false;
    }

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
    this->limitPlayerMovementToScreenArea();

    this->updateBody();
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(m_body.bounds);
}

void Player::setPosition(const sf::Vector2f &position)
{
    m_position = sf::Vector2f(position.x - m_size.x/2, position.y - m_size.y/2);
}

void Player::setAvailableAreaForPlayer(std::shared_ptr<Map> map)
{
    m_map = map;
}
