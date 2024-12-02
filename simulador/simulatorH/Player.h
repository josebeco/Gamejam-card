#include "Carta.h"

#ifndef PLAYERHEADER
#define AMOUNT_CARDS 20
#define PLAYERHEADER
struct Player{
    int adr = 50;
    struct Carta baralho[AMOUNT_CARDS + 5];
    int indBaralho = AMOUNT_CARDS - 1;
    struct Carta mao[AMOUNT_CARDS + 5];
    int maoLength = 0;
    struct Carta emJogo[5];
    bool livreEmJogo[5];
    struct Carta descarte[AMOUNT_CARDS + 5];
    int descarteLength = 0;
};
#endif