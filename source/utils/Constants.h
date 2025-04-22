#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

typedef unsigned int uint;
typedef sf::Vector2f vFloat;
typedef const vFloat &cvFloat;

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
extern const char *DEFEAT_BACKGROUND_IMAGE_PATH;

extern const char *GOT_DAMAGE_ANIMATION_TEXTURE;

namespace MAIN_SPRITE{
    extern const char *TEXTURE_PATH;

    constexpr uint PLAYER_FRAME_SIZE_X = 40;
    constexpr uint PLAYER_FRAME_SIZE_Y = 40;
    constexpr uint PLAYER_FRAME_OFFSET_X = 0;
    constexpr uint PLAYER_FRAME_OFFSET_Y = 0;

    constexpr uint WEAPON_FRAME_SIZE_X = 50;
    constexpr uint WEAPON_FRAME_SIZE_Y = 20;
    constexpr uint WEAPON_FRAME_OFFSET_X = 240;
    constexpr uint WEAPON_FRAME_OFFSET_Y = 0;

    constexpr uint BULLET_FRAME_SIZE_X = 2;
    constexpr uint BULLET_FRAME_SIZE_Y = 2;
    constexpr uint BULLET_FRAME_OFFSET_X = 290;
    constexpr uint BULLET_FRAME_OFFSET_Y = 0;

    constexpr uint ENEMY_FRAME_SIZE_X = 40;
    constexpr uint ENEMY_FRAME_SIZE_Y = 40;
    constexpr uint ENEMY_FRAME_OFFSET_X = 300;
    constexpr uint ENEMY_FRAME_OFFSET_Y = 0;
}

/// correct character rotation to point directly at mouse
constexpr int PLAYER_ROTATION_ANGLE_CORRECTION = 0;//-8;

constexpr int ENEMY_ROTATION_ANGLE_CORRECTION = 0;


constexpr uint WEAPON_TYPES_COUNT = 9;
constexpr uint ZOMBIE_TYPES_COUNT = 6;



#endif // CONSTANTS_H
