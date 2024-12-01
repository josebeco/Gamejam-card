#include "Carta.h"

#ifndef PLAYERHEADER

#define PLAYERHEADER
struct Player{
    int adr = 50;
    struct Carta baralho[25];
    int indBaralho = 19;
    struct Carta mao[25];
    int maoLength = 0;
    struct Carta emJogo[5];
    bool livreEmJogo[5];
    struct Carta descarte[25];
    int descarteLength = 0;
};
#endif