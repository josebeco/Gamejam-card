#include "../modelos/Player.h"
#include "../modelos/Carta.h"
#include "simulatorH/efeitosCartas.h"
#include "simulatorH/HandlerCarta.h"
#include "../lib/fileH/Draw.h"
#include <cstdlib>
#include <ctime>
using namespace std;

#define emJogoSize 5
struct Player jogadores[2];
struct Player jogadorAtual;
int indOponente;

struct Player *getJogadores()
{
    return jogadores;
}

struct Player getPlayer(bool atual)
{
    if (atual)
    {
        return jogadorAtual;
    }
    return jogadores[indOponente];
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

int playCard()
{
    int indCarta = showCards(jogadorAtual.mao, jogadorAtual.maoLength);
    if (indCarta < 0)
    {
        return 2;
    }

    if (!jogadorAtual.mao[indCarta].item && !espacoLivre())
    {
        return 1;
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
        return 2;
    }

    return 0;
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

void resetDecks()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            jogadores[i].deck[j] = 0;
        }
    }
}

bool copyFromDeckToBaralho()
{
    for (int i = 0; i < 2; i++)
    {
        struct Player jogadorCopiado = jogadores[i];
        jogadorCopiado.indBaralho = -1;
        for (int j = 0; j < 20; j++)
        {
            for (int k = 0; k < jogadorCopiado.deck[j]; k++)
            {
                if (jogadorCopiado.indBaralho >= 19)
                {
                    continue;
                }

                jogadorCopiado.baralho[++jogadorCopiado.indBaralho] = copiarCarta(j);
            }
        }
        if (jogadorCopiado.indBaralho < 19)
        {
            return false;
        }
    }
    return true;
}

bool initSimulation()
{
    srand(time(NULL));

    for (int i = 0; i < 2; i++)
    {
        jogadores[i].adr = 50;
        jogadores[i].descarteLength = 0;
        jogadores[i].indBaralho = 19;
        jogadores[i].maoLength = 0;
        for (int j = 0; j < 5; j++)
        {
            jogadores[i].livreEmJogo[j] = true;
        }
        jogadores[i].added_positive_adrenaline = 0;
        jogadores[i].added_negative_adrenaline = 0;
        jogadores[i].split_percentage = 0;
    }

    indOponente = rand() % 2;
    jogadorAtual = jogadores[indOponente ^ 1];
    if (!copyFromDeckToBaralho())
    {
        return false;
    }

    embaralharCartas(jogadorAtual);
    embaralharCartas(jogadores[indOponente]);

    drawCard();
    drawCard();
    drawCard();

    jogadorAtual = jogadores[indOponente];
    indOponente ^= 1;

    drawCard();
    drawCard();
    drawCard();

    return true;
}
