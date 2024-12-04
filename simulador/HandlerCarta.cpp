#include "../modelos/Carta.h"
#include <string>
#include <fstream>
using namespace std;
struct Carta *original;

void lerCartas(){

}

void copiarCarta(struct Carta carta, int ind)
{
    carta.id = original[ind].id;

    carta.mascara = original[ind].mascara;
    carta.ambiente = original[ind].ambiente;
    carta.item = original[ind].item;

    carta.nome = original[ind].nome;
    carta.descricao = original[ind].descricao;

    carta.turnosRestantes = original[ind].turnosRestantes;

    carta.indFuncInPlay = original[ind].indFuncInPlay;
    carta.indFuncPutInPlay = original[ind].indFuncPutInPlay;
    carta.indSprite = original[ind].indSprite;

    carta.jumpscareColor = original[ind].jumpscareColor;
    carta.jumpscareSizeMultipliar = original[ind].jumpscareSizeMultipliar;

    for (int i = 0; i < 10; i++)
    {
        carta.values[i] = original[ind].values[i];
    }
    
    carta.imuneSumir = original[ind].imuneSumir;
    carta.nula = original[ind].nula;
}