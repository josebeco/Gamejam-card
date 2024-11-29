#include "RGB.h"
#ifndef SPRITEHEADER

#define SPRITEHEADER

struct Sprite
{
    struct RGB *pixels;
    int heigth;
    int width;
};

#endif