#include <Player.h>
#include <Carta.h>
#include <cartas.h>
struct Player jogadores[2];
struct Player jogadorAtual;

void setJogadorAtual(int ind){
    jogadorAtual = jogadores[ind];
}

bool checkDeath()
{
    return jogadorAtual.adr <= 0 || jogadorAtual.adr >= 100;
}

void drawCard(){
    jogadorAtual.mao[jogadorAtual.maoLength++] = jogadorAtual.baralho[jogadorAtual.indBaralho--];
}

void playCard(int indCarta){
    putInPlay(jogadorAtual.mao[indCarta].indFuncPutInPlay);
    for (int i = indCarta; i < jogadorAtual.maoLength; i++)
    {
        jogadorAtual.mao[i] = jogadorAtual.mao[i + 1];
    }
    jogadorAtual.maoLength--;
}

void passTurn(){
    for (int i = 0; i < 5; i++)
    {
        if(jogadorAtual.livreEmJogo){
            continue;
        }
        inPlay(jogadorAtual.emJogo[i].indFuncInPlay);
    }
    
}

void deletarCartaEmJogo(){

}