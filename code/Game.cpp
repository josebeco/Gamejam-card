#include "../lib/fileH/Draw.h"
#include "../lib/fileH/Screen.h"
#include "../lib/fileH/HandlerSprites.h"
#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "../simulador/simulatorH/jogo.h"
const struct RGB BLACK = {0, 0, 0};



void cycle()
{
    drawString("cha", 10, 0, BLACK);
    showCards(nullptr, 0);
}
