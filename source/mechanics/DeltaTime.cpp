#include "DeltaTime.h"

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

void DeltaTime::update()
{
    ++m_currentGameTick;
    m_dt = m_deltaTimeClock.restart().asSeconds();
}
