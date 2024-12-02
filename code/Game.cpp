#include "../lib/fileH/Draw.h"
#include "../lib/fileH/Screen.h"
#include "../lib/fileH/HandlerSprites.h"
#include "../lib/fileH/RGB.h"
#include "../lib/fileH/Sprite.h"
#include "../simulador/simulatorH/jogo.h"
struct Sprite *alfabeto;
struct Sprite *cartas;

void initGame()
{
    alfabeto = readSprites("sprites/alfabeto.txt");
    // readSprites("sprites/cartas.txt", cartas);
}



void cycle()
{
}
