#include "../lib/fileH/RGB.h"
#include <string>
using namespace std;

#ifndef CARTAHEADER

#define CARTAHEADER
struct Carta{
    bool mascara, ambiente, item;
    string nome, descricao;
    int turnosRestantes;

    int indFuncPutInPlay;
    int indFuncInPlay;
    int indFuncCheckState;
    int indSprite;

    struct RGB jumpscareColor;
    int jumpscareSizeMultipliar;

    int values[10];
    bool imuneSumir;
}
#endif