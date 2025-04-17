#include "Game.h"

#if defined(__OPTIMIZE__) && __OPTIMIZE__
    // -O1, -O2, -O3
#pragma message("code is optimized")
#else
#pragma message("code is NOT optimized")
#endif

int main()
{
    Game::play();
    return 0;
}
