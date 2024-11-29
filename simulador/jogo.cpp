#include "Player.h"
#include "Carta.h"
#include "cartas.h"
struct Player jogadores[2];
struct Player jogadorAtual;
int indAtual;

void setJogadorAtual(int ind)
{
    jogadorAtual = jogadores[ind];
    indAtual = ind;
}

bool checkDeath()
{
    return jogadorAtual.adr <= 0 || jogadorAtual.adr >= 100;
}

void drawCard()
{
    jogadorAtual.mao[jogadorAtual.maoLength++] = jogadorAtual.baralho[jogadorAtual.indBaralho--];
}

void playCard(int indCarta)
{
    putInPlay(jogadorAtual.mao[indCarta].indFuncPutInPlay, jogadorAtual, jogadores[indAtual ^ 1]);
    for (int i = indCarta; i < jogadorAtual.maoLength; i++)
    {
        jogadorAtual.mao[i] = jogadorAtual.mao[i + 1];
    }
    jogadorAtual.maoLength--;
}

void passTurn()
{
    for (int i = 0; i < 5; i++)
    {
        if (jogadorAtual.livreEmJogo[i])
        {
            continue;
        }
        if (inPlay(jogadorAtual.emJogo[i].indFuncInPlay, jogadorAtual, jogadores[indAtual ^ 1]))
        {
            jogadorAtual.livreEmJogo[i] = true;
            jogadorAtual.emJogo[i].nula = true;
        }
    }
}
