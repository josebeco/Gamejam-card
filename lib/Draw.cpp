#include "fileH/RGB.h"
#include "fileH/Sprite.h"
#include "fileH/Screen.h"
#include "fileH/HandlerSprites.h"
#include "../simulador/simulatorH/Carta.h"
#include <string>
using namespace std;

#define showCardsJ 240
const struct RGB BLACK = {0, 0, 0};
const struct RGB WHITE = {255, 255, 255};

struct Sprite *alfabeto;
struct Sprite *cartas;

void initSprites()
{
    alfabeto = readSprites("sprites/alfabeto.txt");
    // readSprites("sprites/cartas.txt", cartas);
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

void drawSprite(int lui, int luj, struct Sprite sprite, struct RGB color)
{ // left upper corner
    for (int i = 0; i < sprite.heigth; i++)
    {
        for (int j = 0; j < sprite.width; j++)
        {
            if (sprite.pixels[i * sprite.width + j])
            {
                setPixel(lui - i, luj + j, color);
            }
        }
    }
}

void drawString(string frase, int lui, int luj, struct RGB color)
{ // left upper corner
    for (int i = 0; i < frase.length(); i++)
    {
        if(frase[i] == ' '){
            luj += 5;
            continue;
        }

        drawSprite(lui, luj + i, alfabeto[frase[i] - 'a'], color);
        luj += alfabeto[frase[i] - 'a'].width + 1;
    }
}

void showCards(struct Carta cartas[], int length)
{
    drawRectangle(240, showCardsJ, 240, 320 - showCardsJ, WHITE);
    for (int i = 0; i < length; i++)
    {
       drawString(cartas[i].nome, i * 6 + 1, 241, BLACK);
    }
    
}