#include "Screen.h"
#include "HandlerSprites.h"
#include "lib/RGB.h"
#include "SoundPlayer.h"
struct RGB *alfabeto;
struct RGB *cartas;

void initGame(){
    readSprites("sprites/alfabeto.txt", alfabeto);
    //readSprites("sprites/cartas.txt", cartas);

}

void cycle(){

}