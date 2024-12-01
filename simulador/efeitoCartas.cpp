#include "simulatorH/Player.h"
#include "simulatorH/Carta.h"
#include "simulatorH/HandlerCarta.h"
using namespace std;
// ao entrar

void adrenaline_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 0
{
    oponente.adr += carta.values[0];
    atual.adr += carta.valeus[1];
}

void removeCard_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 1
{
    // TODO pega carta esoclhida
    int ind = 0;
    oponente.adr += value[0];
    atual.adr += value[1];

    oponente.emJogo[ind].nula = true;
    oponente.livreEmJogo[ind] = true;

    if (value[2] == 1)
    {
        oponente.descarte[oponente.descarteLength++] = oponente.emJogo[ind];
    }
    else if (value[2] == 2)
    {
        struct Carta nova_carta;
        atual.mao[atual.maoLength++] = copiarCarta(nova_carta, oponente.emJogo[ind].id);
    }
}

void pegarCarta(struct Carta carta, struct Player atual, struct Player oponente) // 2
{
    int ind = 0;
    oponente.adr += value[0];
    atual.adr += value[1];
    if (value[2] == 1)
    {
        // TODO MOSTRAR PILHA DE DESCARTE E PEGAR CARTA
        atual.mao[atual.maoLength++] = atual.descarte[ind];
        while (ind < atual.descarteLength)
        {
            atual.descarte[ind] = atual.descarte[++ind];
        }
        atual.descarteLength--;
    }
    else if (value[2] == 2)
    {
        // TODO MOSTARR BARALHO E PEGAR CARTA
        atual.mao[atual.maoLength] = atual.baralho[ind];
        for (int i = ind; i < atual.indBaralho; i++)
        {
            atual.baralho[ind] = atual.baralho[ind + 1];
        }
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
