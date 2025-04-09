#ifndef DELTATIME_H
#define DELTATIME_H

#include <SFML/System/Clock.hpp>

typedef unsigned long long size_t;

class DeltaTime
{
    DeltaTime();
    DeltaTime(const DeltaTime &) = delete;
    DeltaTime(DeltaTime &&) = delete;
    void operator=(const DeltaTime &) = delete;
    void operator=(DeltaTime &&) = delete;
public:
    static DeltaTime *get();

    float value() const;
    size_t currentGameTick() const;

    void update();

private:
    sf::Clock m_deltaTimeClock;
    float m_dt;
    size_t m_currentGameTick;
};

#endif // DELTATIME_H
