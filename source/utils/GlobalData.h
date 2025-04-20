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
    const sf::Font *getFontOpenSansRegular() const;
    const sf::Texture *getMainSpriteTexture() const;

private:
    sf::Font m_fontOpenSansRegular;
    sf::Texture m_mainSpriteTexture;
};

#endif // GLOBALDATA_H
