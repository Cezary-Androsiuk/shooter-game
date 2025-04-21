#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

#define WINDOW_BACKGROUND_SF_COLOR sf::Color(30, 30, 30)

#define ELEMENT_COLOR_IDLE sf::Color(0, 0, 0, 0)
#define ELEMENT_COLOR_HOVER sf::Color(220, 220, 220, 20)
#define ELEMENT_COLOR_PRESS sf::Color(220, 220, 220, 40)

namespace FONT_PATH{
    extern const char *OPEN_SANS_REGULAR;
    extern const char *INK_FREE;
}
extern const char *INITIAL_DATA_FILE_PATH;
extern const char *RENDER_SHADER1_PATH;
extern const char *MENU_BACKGROUND_IMAGE_PATH;
extern const char *PAUSE_BACKGROUND_IMAGE_PATH;

extern const char *MAIN_SPRITE_TEXTURE_PATH;


typedef unsigned int uint;
typedef sf::Vector2f vFloat;
typedef const vFloat &cvFloat;



#endif // CONSTANTS_H
