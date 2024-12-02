#include "simulatorH/Player.h"
#include "simulatorH/Carta.h"
#include "simulatorH/efeitosCartas.h"
#include <cstdlib>
#include <ctime>
using namespace std;

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
    for (int i = 0; i < 5; i++)
    {
        if (jogadorAtual.livreEmJogo[i] || jogadorAtual.emJogo[i].indFuncInPlay == 1) // se for buff
        {
            continue;
        }
        if (inPlay(jogadorAtual.emJogo[i], jogadorAtual, jogadores[indAtual ^ 1]))
        {
            jogadorAtual.livreEmJogo[i] = true;
            jogadorAtual.emJogo[i].nula = true;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (jogadorAtual.livreEmJogo[i] || jogadorAtual.emJogo[i].indFuncInPlay != 1) // se for buff
        {
            continue;
        }
        if (inPlay(jogadorAtual.emJogo[i], jogadorAtual, jogadores[indAtual ^ 1]))
        {
            jogadorAtual.livreEmJogo[i] = true;
            jogadorAtual.emJogo[i].nula = true;
        }
    }
}

bool playCard(int indCarta)
{
    if (!jogadorAtual.mao[indCarta].item && !espacoLivre)
    {
        return false;
    }

    putInPlay(jogadorAtual.mao[indCarta], jogadorAtual, jogadores[indAtual ^ 1]);
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
    srand(time(NULL));
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