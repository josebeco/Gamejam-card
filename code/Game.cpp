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

void cycle(){

}