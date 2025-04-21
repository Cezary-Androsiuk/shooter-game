#include "Bullet.h"

Bullet::Bullet(int index)
{
    this->index = index;
    printf("+ bullet %d\n", index);
    fflush(stdout);
}

Bullet::~Bullet()
{
    printf("- bullet %d\n", index);
    fflush(stdout);
}
