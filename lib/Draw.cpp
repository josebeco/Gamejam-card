#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "fileH/Screen.h"
#include "fileH/HandlerSprites.h"
#include "../modelos/Carta.h"
#include <string>
#include <ctime>
using namespace std;

#define showCardsJ 240
#define screenWidth 360
const struct RGB BLACK = {0, 0, 0};
const struct RGB YELLOW_PAGE = {204, 201, 172};

struct Sprite *alfabeto;
struct Sprite * spriteCartas;

void delay(int ms){
    clock_t before = clock();
    while(double((clock() - before)) * 1000 / CLOCKS_PER_SEC < ms){}
}

void initSprites()
{
    alfabeto = readSprites("sprites/alfabeto.txt");
    spriteCartas = readSprites("sprites/cartas.txt");
}

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

void drawSprite(int lui, int luj, struct Sprite sprite, struct RGB color, int width_multipliar, int heigth_multipliar)
{ // left upper corner
    int position_i = 0;
    for (int i = 0; i < sprite.heigth; i++)
    {
        for (int ik = 0; ik < heigth_multipliar; ik++)
        {
            position_i++;
            for (int j = 0; j < sprite.width; j++)
            {
                if (sprite.pixels[i * sprite.width + j])
                {
                    for (int jk = 0; jk < width_multipliar; jk++)
                    {
                        setPixel(lui - position_i, luj + j + jk, color);
                    }
                }
            }
        }
    }
}

void drawString(string frase, int lui, int luj, struct RGB color)
{ // left upper corner
    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] == ' ')
        {
            luj += 3;
            continue;
        }

        drawSprite(lui, luj, alfabeto[frase[i] - 'a'], color, 1, 1);
        luj += alfabeto[frase[i] - 'a'].width + 1;
    }
}

void showCards(struct Carta *cartas, int length)
{
    drawRectangle(239, showCardsJ, 240, screenWidth - showCardsJ, YELLOW_PAGE);
    for (int i = 0; i < length; i++)
    {
        drawString(cartas[i].nome, i * 6 + 1, 241, BLACK);
    }
}


void jumpscare(struct Carta carta)
{
    for (int i = 1; i <= carta.jumpscareSizeMultipliar; i++)
    {
        drawSprite( 120 + spriteCartas[carta.indSprite].width * i / 2, screenWidth / 2,spriteCartas[carta.indSprite], carta.jumpscareColor, i, i);
        timerOverride();
        delay(500);
    }
}