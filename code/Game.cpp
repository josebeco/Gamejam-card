#include "../lib/fileH/Draw.h"
#include "../lib/fileH/Screen.h"
#include "../lib/fileH/HandlerSprites.h"
#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "../simulador/simulatorH/jogo.h"
const struct RGB BLACK = {0, 0, 0};
const struct RGB YELLOW_PAGE = {200, 200, 200};



void cycle()
{
    showCards(nullptr, 0);
    drawString("mascara do cha", 230, 260, BLACK);
}
