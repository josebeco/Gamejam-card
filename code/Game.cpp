#include "Screen.h"
#include "HandlerSprites.h"
#include "../lib/RGB.h"
#include "SoundPlayer.h"
#include "../lib/Sprite.h"
struct Sprite *alfabeto;
struct Sprite *cartas;


void initGame(){
    alfabeto = readSprites("sprites/alfabeto.txt");
    //readSprites("sprites/cartas.txt", cartas);

}

void drawRectangle(int lui, int luj, int width, int heigth, struct RGB color){ // left upper corner
    while (--heigth >= 0)
    {
        for (int i = 0; i < width; i++)
        {
            setPixel(lui - heigth, luj + i, color);
        }
        
    }   
}

void putSprite(int lui, int luj, struct Sprite sprite){ // left upper corner

}

void cycle(){
    
}

