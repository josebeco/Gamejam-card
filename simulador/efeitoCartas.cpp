#include "../modelos/Player.h"
#include "../modelos/Carta.h"
#include "simulatorH/HandlerCarta.h"
#include "simulatorH/jogo.h"
using namespace std;
int added_value_positive_adrenaline = 0;
int added_value_negative_adrenaline = 0;
// ao entrar

void adrenaline_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 0
{
    oponente.adr += carta.values[0];
    atual.adr += carta.values[1];
}

void removeCard_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 1
{
    if (carta.values[3] != -1 && atual.adr < carta.values[3] || carta.values[4] != -1 && atual.adr > carta.values[4])
    {
        return;
    }

    // TODO pega carta esoclhida
    int ind = 0;
    oponente.adr += carta.values[0];
    atual.adr += carta.values[1];

    oponente.emJogo[ind].nula = true;
    oponente.livreEmJogo[ind] = true;

    if (carta.values[2] == 1)
    {
        oponente.descarte[oponente.descarteLength++] = oponente.emJogo[ind];
    }
    else if (carta.values[2] == 2)
    {
        struct Carta nova_carta;
        copiarCarta(nova_carta, oponente.emJogo[ind].id);
        atual.mao[atual.maoLength++] = nova_carta;
    }
}

void pegarCarta_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 2
{
    int ind = 0;
    oponente.adr += carta.values[0];
    atual.adr += carta.values[1];

    if (carta.values[2] == 1 && atual.descarteLength > 0)
    {
        // TODO MOSTRAR PILHA DE DESCARTE E PEGAR CARTA
        atual.mao[atual.maoLength++] = atual.descarte[ind];
        while (ind < atual.descarteLength)
        {
            atual.descarte[ind] = atual.descarte[++ind];
        }
        atual.descarteLength--;
    }
    else if (carta.values[2] == 2 && atual.indBaralho > -1)
    {
        // TODO MOSTARR BARALHO E PEGAR CARTA
        atual.mao[atual.maoLength] = atual.baralho[ind];
        for (int i = ind; i < atual.indBaralho; i++)
        {
            atual.baralho[ind] = atual.baralho[ind + 1];
        }
        atual.indBaralho--;
        embaralharCartas(atual);
    }
}

void buff_PutInPlay(struct Carta carta, struct Player atual, struct Player oponente) // 3
{
    if (carta.values[3] != -1 && atual.adr < carta.values[3] || carta.values[4] != -1 && atual.adr > carta.values[4])
    {
        return;
    }

    added_value_positive_adrenaline += carta.values[0];
    added_value_negative_adrenaline += carta.values[1];
}

void (*funcPutInPlay[4])(struct Carta, struct Player, struct Player) = {&adrenaline_PutInPlay, &removeCard_PutInPlay, &removeCard_PutInPlay, &buff_PutInPlay};

void putInPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    funcPutInPlay[carta.indFuncPutInPlay](carta, atual, oponente);
}

bool adrenaline_InPlay(struct Carta carta, struct Player atual, struct Player oponente)
{ // retorna se a carta morreu, 0
    if (carta.values[7] != -1 && atual.adr < carta.values[7] || carta.values[8] != -1 && atual.adr > carta.values[8])
    {
        return true;
    }

    if (carta.values[9] != 2)
    {
        carta.turnosRestantes--;
    }

    if (carta.values[9] != 1 || carta.turnosRestantes == 0)
    {
        if (carta.values[5] > 0)
        {
            oponente.adr += added_value_positive_adrenaline;
        }
        else if (carta.values[5] < 0)
        {
            oponente.adr += added_value_negative_adrenaline;
        }

        oponente.adr += carta.values[5];
        atual.adr += carta.values[6];
    }

    return carta.turnosRestantes == 0;
}

bool buff_InPlay(struct Carta carta, struct Player atual, struct Player oponente) // 1
{
    if (carta.values[7] != -1 && atual.adr < carta.values[7] || carta.values[8] != -1 && atual.adr > carta.values[8])
    {
        added_value_positive_adrenaline -= carta.values[5];
        added_value_negative_adrenaline -= carta.values[6];
        return true;
    }

    if (carta.values[9] != 2)
    {
        carta.turnosRestantes--;
    }

    if (carta.turnosRestantes == 0)
    {
        added_value_positive_adrenaline -= carta.values[5];
        added_value_negative_adrenaline -= carta.values[6];
    }

    return carta.turnosRestantes == 0;
}

bool (*funcInPlay[2])(struct Carta, struct Player, struct Player) = {&adrenaline_InPlay, &buff_InPlay};

bool inPlay(struct Carta carta, struct Player atual, struct Player oponente)
{
    // cham metodo
    return false;
}
