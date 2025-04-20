#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <SFML/Graphics.hpp>

class GlobalData
{
    void loadFonts();
    void loadMainSpriteTexture();

    GlobalData();

    GlobalData(const GlobalData &) = delete;
    GlobalData(GlobalData &&) = delete;
    void operator=(const GlobalData &) = delete;
    void operator=(GlobalData &&) = delete;
public:
    static GlobalData *getInstance();

    /// removes all overload functions, to prevent calling it from an instance (i guess)
    static GlobalData& getInstance(GlobalData&) = delete;
    static GlobalData& getInstance(const GlobalData&) = delete;
    static GlobalData& getInstance(GlobalData&&) = delete;

    /// GETTERS
    const sf::Font &getFontOpenSansRegular() const;
    const sf::Font &getFontInkFree() const;
    const sf::Texture &getMainSpriteTexture() const;
    const sf::Vector2f &getWindowSize() const;
    const sf::Vector2f &getWindowRatio() const;
    const sf::Vector2f &getMousePosition() const;

    void setWindowSize(const sf::Vector2f &windowSize);
    void setMousePosition(const sf::Vector2f &mousePosition);

private:
    sf::Font m_fontOpenSansRegular;
    sf::Font m_fontInkFree;
    sf::Texture m_mainSpriteTexture;

    sf::Vector2f m_windowSize;
    sf::Vector2f m_windowRatio;

    sf::Vector2f m_mousePosition;
};

#endif // GLOBALDATA_H
