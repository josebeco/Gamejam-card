#include "simulatorH/Player.h"
#include "simulatorH/Carta.h"
#include "simulatorH/HandlerCarta.h"
#define ID_REZA 1
#define ID_SERINGA 1
#define ID_FOMO 1
#define ID_CHAMADA 1
using namespace std;
// ao entrar

void adrenaline_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    oponente.adr += carta.values[0];
    atual.adr += carta.valeus[1];
}

void removeCard_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    // TODO pega carta esoclhida
    int ind = 0;
    oponente.adr += value[0];
    atual.adr += value[1];

    oponente.emJogo[ind].nula = true;
    oponente.livreEmJogo[ind] = true;

    if (carta.id == ID_REZA)
    {
        oponente.descarte[oponente.descarteLength++] = oponente.emJogo[ind];
    }
    else if (carta.id == ID_SERINGA)
    {
        struct Carta nova_carta;
        atual.mao[atual.maoLength++] = copiarCarta(nova_carta, oponente.emJogo[ind].id);
    }
}

void pegarCarta(struct Carta carta, struct Player atual, struct Player oponente)
{
    int ind = 0;
    oponente.adr += value[0];
    atual.adr += value[1];
    if (carta.id == ID_CHAMADA)
    {
        // TODO MOSTRAR PILHA DE DESCARTE E PEGAR CARTA
        atual.mao[atual.maoLength++] = atual.descarte[ind];
        while (ind < atual.descarteLength)
        {
            atual.descarte[ind] = atual.descarte[++ind];
        }
        atual.descarteLength--;
    }else if(carta.id == ID_FOMO){
        // TODO MOSTARR BARALHO E PEGAR CARTA
    }
}

void putInPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    // cham metodo
}

bool inPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    // cham metodo
    return false;
}
