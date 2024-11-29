#include "fileH/RGB.h"
#include "fileH/Sprite.h"
#include "fileH/Screen.h"

void drawRectangle(int lui, int luj, int heigth, int width, struct RGB color)
{ // left upper corner
    while (--heigth >= 0)
    {
        for (int i = 0; i < width; i++)
        {
            setPixel(lui - heigth, luj + i, color);
        }
    }
}

void drawSprite(int lui, int luj, struct Sprite sprite)
{ // left upper corner
    for (int i = 0; i < sprite.heigth; i++)
    {
        for (int j = 0; j < sprite.width; j++)
        {
            setPixel(lui - i, luj + j, sprite.pixels[i * sprite.width + j]);
        }
    }
}