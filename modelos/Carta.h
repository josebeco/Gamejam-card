#include "RGB.h"
#include <string>
using namespace std;

#ifndef CARTAHEADER

#define CARTAHEADER
struct Carta{
    int id;
    bool mascara, ambiente, item;
    string nome, descricao;
    int turnosRestantes;

    int indFuncPutInPlay;
    int indFuncInPlay;
    int indSprite;

    struct RGB jumpscareColor;
    int jumpscareSizeMultipliar;

    int values[10]; // 0 - 4 put in play 5 - 9 in pĺay
    bool imuneSumir;
    bool nula = false;
};
#endif