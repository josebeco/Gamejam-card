#include "../modelos/Player.h"
#include "../modelos/Carta.h"
#include "../lib/fileH/Draw.h"
#include "simulatorH/HandlerCarta.h"
#include "simulatorH/jogo.h"
using namespace std;

bool adrenaline_InPlay(struct Carta &carta, struct Player &atual, struct Player &oponente)
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
            oponente.adr += atual.added_positive_adrenaline * oponente.split_percentage / 100;
            atual.adr += atual.added_positive_adrenaline * (100 - oponente.split_percentage) / 100;
        }
        else if (carta.values[5] < 0)
        {
            oponente.adr += atual.added_negative_adrenaline * oponente.split_percentage / 100;
            atual.adr += atual.added_negative_adrenaline * (100 - oponente.split_percentage) / 100;
        }

        oponente.adr += carta.values[5] * oponente.split_percentage / 100;
        atual.adr += carta.values[6] + carta.values[5] * (100 - oponente.split_percentage) / 100;
    }

    return carta.turnosRestantes <= 0;
}

bool buff_InPlay(struct Carta &carta, struct Player &atual, struct Player &oponente) // 1
{
    if (carta.values[8] != -1 && atual.adr < carta.values[8] || carta.values[9] != -1 && atual.adr > carta.values[9])
    {
        atual.added_positive_adrenaline -= carta.values[0];
        atual.added_negative_adrenaline -= carta.values[1];
        atual.split_percentage -= carta.values[2];
        return true;
    }

    if (carta.values[7] != 0)
    {
        return false;
    }

    carta.turnosRestantes--;

    if (carta.turnosRestantes <= 0)
    {
        atual.added_positive_adrenaline -= carta.values[0];
        atual.added_negative_adrenaline -= carta.values[1];
        atual.split_percentage -= carta.values[2];
    }

    return carta.turnosRestantes <= 0;
}

bool (*funcInPlay[2])(struct Carta &, struct Player &, struct Player &) = {&adrenaline_InPlay, &buff_InPlay};

bool inPlay(struct Carta &carta, struct Player &atual, struct Player &oponente)
{
    return funcInPlay[carta.indFuncInPlay](carta, atual, oponente);
}

// ao entrar

void adrenaline_PutInPlay(struct Carta &carta, struct Player &atual, struct Player &oponente) // 0
{
    oponente.adr += carta.values[0] * oponente.split_percentage / 100;
    atual.adr += carta.values[1] + carta.values[0] * (100 - oponente.split_percentage) / 100;
}

void removeCard_PutInPlay(struct Carta &carta, struct Player &atual, struct Player &oponente) // 1
{
    if (carta.values[3] != -1 && atual.adr < carta.values[3] || carta.values[4] != -1 && atual.adr > carta.values[4])
    {
        return;
    }

    // TODO pega carta esoclhida
    int ind = 0;

    oponente.adr += carta.values[0] * oponente.split_percentage / 100;
    atual.adr += carta.values[1] + carta.values[0] * (100 - oponente.split_percentage) / 100;

    oponente.emJogo[ind].nula = true;
    oponente.livreEmJogo[ind] = true;

    if (oponente.emJogo[ind].indFuncInPlay == 1)
    {
        oponente.emJogo[ind].turnosRestantes = 0;
        buff_InPlay(oponente.emJogo[ind], oponente, atual);
    }

    if (carta.values[2] == 1)
    {
        oponente.descarte[oponente.descarteLength++] = oponente.emJogo[ind];
    }
    else if (carta.values[2] == 2)
    {
        atual.mao[atual.maoLength++] = copiarCarta(oponente.emJogo[ind].id);
    }
}

void pegarCarta_PutInPlay(struct Carta &carta , struct Player &atual, struct Player &oponente) // 2
{
    int ind = 0;
    oponente.adr += carta.values[0] * oponente.split_percentage / 100;
    atual.adr += carta.values[0] * (100 - oponente.split_percentage) / 100;
    atual.adr += carta.values[1];

    if (carta.values[2] == 1 && atual.descarteLength > 0)
    {
        ind = showCards(atual.descarte, atual.descarteLength);
        if (ind == -1)
        {
            return;
        }
        atual.mao[atual.maoLength++] = copiarCarta(atual.descarte[ind].id);
        atual.descarteLength--;
        while (ind < atual.descarteLength)
        {
            atual.descarte[ind] = atual.descarte[++ind];
        }
    }
    else if (carta.values[2] == 2 && atual.indBaralho > -1)
    {
        ind = showCards(atual.baralho, atual.indBaralho + 1);
        if (ind == -1)
        {
            return;
        }
        atual.mao[atual.maoLength] = atual.baralho[ind];
        for (int i = ind; i < atual.indBaralho; i++)
        {
            atual.baralho[ind] = atual.baralho[ind + 1];
        }
        atual.indBaralho--;
        embaralharCartas(atual);
    }
}

void buff_PutInPlay(struct Carta &carta, struct Player &atual, struct Player &oponente) // 3
{
    if (carta.values[3] != -1 && atual.adr < carta.values[3] || carta.values[4] != -1 && atual.adr > carta.values[4])
    {
        return;
    }

    atual.added_positive_adrenaline += carta.values[0];
    atual.added_negative_adrenaline += carta.values[1];
    atual.split_percentage += carta.values[2];
}

void (*funcPutInPlay[4])(struct Carta &, struct Player &, struct Player &) = {&adrenaline_PutInPlay, &removeCard_PutInPlay, &removeCard_PutInPlay, &buff_PutInPlay};

void putInPlay(struct Carta &carta, struct Player &atual, struct Player &oponente)
{
    funcPutInPlay[carta.indFuncPutInPlay](carta, atual, oponente);
}
