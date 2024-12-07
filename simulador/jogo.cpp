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
int indAtual;
int indOponente;

struct Player *getJogadores()
{
    return jogadores;
}

struct Player &getPlayer(bool atual)
{
    if (atual)
    {
        return jogadores[indAtual];
    }
    return jogadores[indOponente];
}

bool checkDeath()
{
    return jogadores[indAtual].adr <= 0 || jogadores[indAtual].adr >= 100;
}

bool drawCard()
{
    if (jogadores[indAtual].indBaralho < 0)
    {
        return false;
    }

    copiarCarta(jogadores[indAtual].mao[jogadores[indAtual].maoLength++], jogadores[indAtual].baralho[jogadores[indAtual].indBaralho--]);
    return true;
}

bool espacoLivre()
{
    for (int i = 0; i < 5; i++)
    {
        if (jogadores[indAtual].livreEmJogo[i])
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
        if (jogadores[indAtual].livreEmJogo[i] || jogadores[indAtual].emJogo[i].indFuncInPlay == 1) // se for buff
        {
            continue;
        }

        if (inPlay(jogadores[indAtual].emJogo[i], jogadores[indAtual], jogadores[indOponente]))
        {
            jogadores[indAtual].livreEmJogo[i] = true;
            jogadores[indAtual].emJogo[i].nula = true;
            copiarCarta(jogadores[indAtual].descarte[jogadores[indAtual].descarteLength++], jogadores[indAtual].emJogo[i]);
        }

        jumpscare(jogadores[indAtual].emJogo[i]);
    }

    for (int i = 0; i < emJogoSize; i++)
    {
        if (jogadores[indAtual].livreEmJogo[i] || jogadores[indAtual].emJogo[i].indFuncInPlay != 1) // se for buff
        {
            continue;
        }

        if (inPlay(jogadores[indAtual].emJogo[i], jogadores[indAtual], jogadores[indOponente]))
        {
            jogadores[indAtual].livreEmJogo[i] = true;
            jogadores[indAtual].emJogo[i].nula = true;
            copiarCarta(jogadores[indAtual].descarte[jogadores[indAtual].descarteLength++], jogadores[indAtual].emJogo[i]);
        }

        jumpscare(jogadores[indAtual].emJogo[i]);
    }

    indAtual ^= 1;
    indOponente ^= 1;
}

int playCard()
{
    int indCarta = showCards(jogadores[indAtual].mao, jogadores[indAtual].maoLength);
    if (indCarta < 0)
    {
        return 2;
    }

    if (!jogadores[indAtual].mao[indCarta].item && !espacoLivre())
    {
        return 1;
    }

    if (!jogadores[indAtual].mao[indCarta].item)
    {
        for (int i = 0; i < emJogoSize; i++)
        {
            if (jogadores[indAtual].livreEmJogo[i])
            {
                jogadores[indAtual].livreEmJogo[i] = false;
                jogadores[indAtual].emJogo[i] = jogadores[indAtual].mao[indCarta];
                break;
            }
        }
    }

    putInPlay(jogadores[indAtual].mao[indCarta], jogadores[indAtual], jogadores[indOponente]);
    jumpscare(jogadores[indAtual].mao[indCarta]);

    if(jogadores[indAtual].mao[indCarta].item){
        copiarCarta(jogadores[indAtual].descarte[jogadores[indAtual].descarteLength++] , jogadores[indAtual].mao[indCarta]);
    }

    for (int i = indCarta; i < jogadores[indAtual].maoLength - 1; i++)
    {
        jogadores[indAtual].mao[i] = jogadores[indAtual].mao[i + 1];
    }
    jogadores[indAtual].maoLength--;

    if (jogadores[indAtual].mao[indCarta].mascara)
    {
        return 2;
    }

    return 0;
}

void embaralharCartas(struct Player &jogador)
{
    bool indUsado[jogador.indBaralho + 1];
    struct Carta *mediador;
    mediador = new struct Carta[20];
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

        copiarCarta(mediador[i], jogador.baralho[ind]);
    }

    for (int i = 0; i < jogador.indBaralho + 1; i++)
    {
        copiarCarta(jogador.baralho[i], mediador[i]);
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
        jogadores[i].indBaralho = -1;
        for (int j = 0; j < 20; j++)
        {
            for (int k = 0; k < jogadores[i].deck[j]; k++)
            {
                if (jogadores[i].indBaralho >= 19)
                {
                    continue;
                }

                jogadores[i].baralho[++jogadores[i].indBaralho] = copiarCarta(j);
            }
        }
        if (jogadores[i].indBaralho < 19)
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
            jogadores[i].emJogo[j].nula = true;
        }
        jogadores[i].added_positive_adrenaline = 0;
        jogadores[i].added_negative_adrenaline = 0;
        jogadores[i].split_percentage = 100;
    }

    indOponente = rand() % 2;
    indAtual = indOponente ^ 1;
    if (!copyFromDeckToBaralho())
    {
        return false;
    }

    embaralharCartas(jogadores[indAtual]);
    embaralharCartas(jogadores[indOponente]);

    drawCard();
    drawCard();
    drawCard();

    indOponente ^= 1;
    indAtual ^= 1;

    drawCard();
    drawCard();
    drawCard();

    return true;
}
