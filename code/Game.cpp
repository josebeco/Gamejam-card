#include "../lib/fileH/Draw.h"
#include "../lib/fileH/Screen.h"
#include "../lib/fileH/HandlerSprites.h"
#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "../simulador/simulatorH/jogo.h"
const struct RGB BLACK = {0, 0, 0};
const struct RGB YELLOW_PAGE = {204, 201, 172};
int indKi = 0;
int indKj = 0;
int state = 0; // 0-menu 1-game 

void incKi(){
    indKi++;
}

void incKj(){
    indKj++;
}

void decKi(){
    indKi--;
}

void decKj(){
    indKj--;
}

void cycle()
{
    
}

