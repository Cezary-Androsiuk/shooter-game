#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    void initWindow();

    Game();


public: static void play();
private:
    bool running() const;


    sf::RenderWindow* m_window;
    sf::Event m_currentEvent;
};

#endif // GAME_H
