#include "../modelos/Player.h"
#include "../modelos/Carta.h"
#include "simulatorH/efeitosCartas.h"
#include "../lib/fileH/Draw.h"
#include <cstdlib>
#include <ctime>
using namespace std;

#define emJogoSize 5
struct Player jogadores[2];
struct Player jogadorAtual;
int indOponente;


bool checkDeath()
{
    return jogadorAtual.adr <= 0 || jogadorAtual.adr >= 100;
}

bool drawCard()
{
    if (jogadorAtual.indBaralho < 0)
    {
        return false;
    }

    jogadorAtual.mao[jogadorAtual.maoLength++] = jogadorAtual.baralho[jogadorAtual.indBaralho--];
    return true;
}

bool espacoLivre()
{
    for (int i = 0; i < 5; i++)
    {
        if (jogadorAtual.livreEmJogo[i])
        {
            return true;
        }
    }
    return false;
}

void passTurn()
{
    for (int i = 0; i < emJogoSize; i++)
    {
        if (jogadorAtual.livreEmJogo[i] || jogadorAtual.emJogo[i].indFuncInPlay == 1) // se for buff
        {
            continue;
        }
        if (inPlay(jogadorAtual.emJogo[i], jogadorAtual, jogadores[indOponente]))
        {
            jogadorAtual.livreEmJogo[i] = true;
            jogadorAtual.emJogo[i].nula = true;
        }
        jumpscare(jogadorAtual.emJogo[i]);
    }

    for (int i = 0; i < emJogoSize; i++)
    {
        if (jogadorAtual.livreEmJogo[i] || jogadorAtual.emJogo[i].indFuncInPlay != 1) // se for buff
        {
            continue;
        }
        if (inPlay(jogadorAtual.emJogo[i], jogadorAtual, jogadores[indOponente]))
        {
            jogadorAtual.livreEmJogo[i] = true;
            jogadorAtual.emJogo[i].nula = true;
        }
        jumpscare(jogadorAtual.emJogo[i]);
    }
    jogadorAtual = jogadores[indOponente];
    indOponente ^= 1;
}

bool playCard(int indCarta)
{
    if (!jogadorAtual.mao[indCarta].item && !espacoLivre())
    {
        return false;
    }

    if (!jogadorAtual.mao[indCarta].item)
    {
        for (int i = 0; i < emJogoSize; i++)
        {
            if (jogadorAtual.livreEmJogo[i])
            {
                jogadorAtual.livreEmJogo[i] = false;
                jogadorAtual.emJogo[i] = jogadorAtual.mao[indCarta];
                break;
            }
        }
    }

    putInPlay(jogadorAtual.mao[indCarta], jogadorAtual, jogadores[indOponente ^ 1]);
    jumpscare(jogadorAtual.mao[indCarta]);
    for (int i = indCarta; i < jogadorAtual.maoLength - 1; i++)
    {
        jogadorAtual.mao[i] = jogadorAtual.mao[i + 1];
    }
    jogadorAtual.maoLength--;

    if (jogadorAtual.mao[indCarta].mascara)
    {
        passTurn();
    }

    return true;
}

void embaralharCartas(struct Player jogador)
{
    bool indUsado[jogador.indBaralho + 1];
    struct Carta mediador[jogador.indBaralho + 1];
    for (int i = 0; i < jogador.indBaralho + 1; i++)
    {
        indUsado[i] = false;
    }

    for (int i = 0; i < jogador.indBaralho + 1; i++)
    {
        int ind;
        do
        {
            ind = rand() % (jogador.indBaralho + 1);
        } while (indUsado[ind]);

        indUsado[ind] = true;
        mediador[i] = jogador.baralho[ind];
    }

    for (int i = 0; i < jogador.indBaralho + 1; i++)
    {
        jogador.baralho[i] = mediador[i];
    }
}

void initSimulation(){
    srand(time(NULL));
    indOponente = rand() % 2;
    jogadorAtual = jogadores[indOponente ^ 1];
    embaralharCartas(jogadorAtual);
    embaralharCartas(jogadores[indOponente]);
}

