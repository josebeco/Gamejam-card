#include "RGB.h"
#include <string>
using namespace std;

#ifndef CARTAHEADER

#define CARTAHEADER
struct Carta{
    int id;
    string nome, descricao;
    bool mascara, ambiente, item;
    int turnosRestantes;

    int indFuncPutInPlay;
    int indFuncInPlay;
    int indSprite;

    struct RGB jumpscareColor;
    int jumpscareSizeMultipliar;

    int values[10]; // 0 - 4 put in play 5 - 9 in pĺay
    bool nula = false;
};
#endif