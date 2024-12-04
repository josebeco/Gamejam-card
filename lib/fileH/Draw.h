#include "../../modelos/RGB.h"
#include "../../modelos/Sprite.h"
#include "../../modelos/Carta.h"
#include <string>
using namespace std;

void initSprites();
void drawRectangle(int, int, int, int, struct RGB);
void drawSprite(int, int, struct Sprite, struct RGB, int, int);
void drawString(string , int , int , struct RGB);
void showCards(struct Carta *, int);
void jumpscare(struct Carta);