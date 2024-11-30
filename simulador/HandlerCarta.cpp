#include "simulatorH/Carta.h"
struct Carta *cartas;

void copiarCarta(struct Carta carta, int ind)
{
    carta.id = cartas[ind].id;

    carta.mascara = cartas[ind].mascara;
    carta.ambiente = cartas[ind].ambiente;
    carta.item = cartas[ind].item;

    carta.nome = cartas[ind].nome;
    carta.descricao = carta[ind].descricao;

    carta.turnosRestantes = carta[ind].turnosRestantes;

    carta.indFuncInPlay = carta[ind].indFuncInPlay;
    carta.indFuncPutInPlay = carta[ind].indFuncPutInPlay;
    carta.indSprite = carta[ind].indSprite;

    carta.jumpscareColor = carta[ind].jumpscareColor;
    carta.jumpscareSizeMultipliar = carta[ind].jumpscareSizeMultipliar;

    carta.values = carta[ind].values;
    carta.imuneSumir = carta[ind].imuneSumir;
    carta.nula = carta[ind].nula;
}