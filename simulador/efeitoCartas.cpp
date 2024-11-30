#include "simulatorH/Player.h"
#include "simulatorH/Carta.h"
#define ID_REZA 1
#define ID_SERINGA 1
using namespace std;
// ao entrar

void adrenalinePutInPlay(struct Carta carta, struct Player atual, struct Player oponente){ 
    oponente.adr += carta.values[0];
    atual.adr += carta.valeus[1];
}

void removeCardPutInPlay(struct Carta carta, struct Player atual, struct Player oponente){
    // TODO pega carta esoclhida
    int ind = 0;
    if(carta.id == ID_REZA){
        oponente.emJogo[ind].nula = true;
        oponente.livreEmJogo[ind] = true;
        oponente.descarte[oponente.descarteLength++] = oponente.emJogo[ind];
    }else if(carta.id == ID_SERINGA){
        oponente.emJogo[ind].nula = true;
        oponente.livreEmJogo[ind] = true;
    }
}


void putInPlay(struct Carta carta, struct Player atual, struct Player oponente){
    // cham metodo
}

bool inPlay(struct Carta carta, struct Player atual, struct Player oponente){
    // cham metodo
    return false;
}



