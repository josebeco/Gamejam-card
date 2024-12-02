#include "RGB.h"
#include "Sprite.h"
#include "../../simulador/simulatorH/Carta.h"
#include <string>
using namespace std;

void initSprites();
void drawRectangle(int, int, int, int, struct RGB);
void drawSprite(int, int, struct Sprite, struct RGB);
void drawString(string , int , int , struct RGB);
void showCards(struct Carta *, int);