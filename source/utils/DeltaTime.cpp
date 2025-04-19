#include "DeltaTime.h"

sf::Clock DeltaTime::printDelayer;

DeltaTime::DeltaTime() {}

DeltaTime *DeltaTime::get()
{
    static DeltaTime dt;
    return &dt;
}

float DeltaTime::value() const
{
    return m_dt;
}

size_t DeltaTime::currentGameTick() const
{
    return m_currentGameTick;
}

bool DeltaTime::canPrint()
{
    if(printDelayer.getElapsedTime().asMilliseconds() >= PRINT_DELAY_MS)
    {
        printDelayer.restart();
        return true;
    }
    return false;
}

void DeltaTime::update()
{
    ++m_currentGameTick;
    m_dt = m_deltaTimeClock.restart().asSeconds();
}
