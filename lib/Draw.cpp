#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "fileH/Screen.h"
#include "fileH/HandlerSprites.h"
#include "../modelos/Carta.h"
#include "../modelos/Player.h"
#include "../simulador/simulatorH/jogo.h"
#include "../simulador/simulatorH/HandlerCarta.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define showCardsJ 220
#define screenWidth 360
const struct RGB BLACK = {0, 0, 0};
const struct RGB YELLOW_PAGE = {204, 201, 172};
const struct RGB WHITE = {255, 255, 255};
const struct RGB RED = {170, 0, 0};

struct Sprite *alfabeto;
struct Sprite *spriteCartas;
struct Sprite *extras;
struct Sprite *numbers;

int state = 0; // 0-menu 1-deck 2-game
int indKi = 0;
int indKj = 0;
bool confirmado;
bool cancelado;

void incKi()
{
    indKi++;
}

void incKj()
{
    indKj++;
}

void decKi()
{
    indKi--;
}

void decKj()
{
    indKj--;
}

void confirmar()
{
    confirmado = true;
}

void cancelar()
{
    cancelado = true;
}

void delay(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void initSprites()
{
    alfabeto = readSprites("sprites/alfabeto.txt");
    spriteCartas = readSprites("sprites/cartas.txt");
    extras = readSprites("sprites/extras.txt");
    numbers = readSprites("sprites/numero.txt");
}

void drawRectangle(int lui, int luj, int heigth, int width, struct RGB color)
{ // left upper corner
    while (--heigth >= 0)
    {
        for (int i = 0; i < width; i++)
        {
            setPixel(lui - heigth, luj + i, color);
        }
    }
}

void drawSprite(int lui, int luj, struct Sprite sprite, struct RGB color, int width_multipliar, int heigth_multipliar, bool drawBackground)
{ // left upper corner
    int position_i = 0;
    for (int i = 0; i < sprite.heigth; i++)
    {
        for (int ik = 0; ik < heigth_multipliar; ik++)
        {
            for (int j = 0; j < sprite.width; j++)
            {
                if (sprite.pixels[i * sprite.width + j])
                {
                    for (int jk = 0; jk < width_multipliar; jk++)
                    {
                        setPixel(lui - position_i, luj + j * width_multipliar + jk, color);
                    }
                }
                else if (drawBackground)
                {
                    for (int jk = 0; jk < width_multipliar; jk++)
                    {
                        setPixel(lui - position_i, luj + j * width_multipliar + jk, WHITE);
                    }
                }
            }
            position_i++;
        }
    }
}
int getStringLength(string frase)
{
    int r = 0;
    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] == ' ')
        {
            r += 3;
            continue;
        }
        if (frase[i] == '-')
        {

            r += numbers[9].width + 1;
        }
        else if (frase[i] >= '0' && frase[i] <= '9')
        {

            r += numbers[frase[i] - '0'].width + 1;
        }
        else
        {

            r += alfabeto[frase[i] - 'a'].width + 1;
        }
    }
    return r;
}
void drawString(string frase, int lui, int luj, struct RGB color, int width_multipliar, int heigth_multipliar)
{ // left upper corner
    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] == ' ')
        {
            luj += 3 * width_multipliar;
            continue;
        }
        if (frase[i] == '-')
        {
            drawSprite(lui, luj, numbers[9], color, width_multipliar, heigth_multipliar, false);
            luj += (numbers[9].width + 1) * width_multipliar;
        }
        else if (frase[i] >= '0' && frase[i] <= '9')
        {
            drawSprite(lui, luj, numbers[frase[i] - '0'], color, width_multipliar, heigth_multipliar, false);
            luj += (numbers[frase[i] - '0'].width + 1) * width_multipliar;
        }
        else
        {
            drawSprite(lui, luj, alfabeto[frase[i] - 'a'], color, width_multipliar, heigth_multipliar, false);
            luj += (alfabeto[frase[i] - 'a'].width + 1) * width_multipliar;
        }
    }
}

void drawStringLimited(int lui, int luj, int heigth, int width, string frase, struct RGB color, int width_multipliar, int heigth_multipliar)
{
    int lujO = luj;
    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] == ' ')
        {
            luj += 3 * width_multipliar;
            if (luj + 50 * width_multipliar >= width)
            {
                lui -= 6 * heigth_multipliar;
                luj = lujO;
            }
            continue;
        }
        if (frase[i] == '-')
        {
            drawSprite(lui, luj, numbers[9], color, width_multipliar, heigth_multipliar, false);
            luj += (numbers[9].width + 1) * width_multipliar;
        }
        else if (frase[i] >= '0' && frase[i] <= '9')
        {
            drawSprite(lui, luj, numbers[frase[i] - '0'], color, width_multipliar, heigth_multipliar, false);
            luj += (numbers[frase[i] - '0'].width + 1) * width_multipliar;
        }
        else
        {
            drawSprite(lui, luj, alfabeto[frase[i] - 'a'], color, width_multipliar, heigth_multipliar, false);
            luj += (alfabeto[frase[i] - 'a'].width + 1) * width_multipliar;
        }
    }
}

void drawCardWithDescription(struct Carta carta)
{
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawSprite(230, 10, spriteCartas[carta.indSprite], carta.jumpscareColor, 2, 2, true);
    drawString(carta.nome, 230, 80, BLACK, 2, 2);
    drawStringLimited(210, 80, 230, screenWidth - 90, carta.descricao, BLACK, 1, 1);
}

void drawDeckBuilderMenu(struct Carta *original)
{
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawRectangle(239, screenWidth / 2, 240, 1, BLACK);
    drawString("player 1", 230, screenWidth / 2 - getStringLength("player 1") - 50, BLACK, 1, 1);
    drawString("player 2", 230, screenWidth / 2 + 50, BLACK, 1, 1);

    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                drawSprite(220 - i * 45, 5 + j * 46 + k * screenWidth / 2, spriteCartas[original[i * 4 + j].indSprite], BLACK, 1, 1, true);
            }
        }
    }
}

int deckCardShow(struct Carta carta, int qtdO) // retorna qtd
{
    cancelado = false;
    confirmado = false;
    indKj = qtdO;

    drawCardWithDescription(carta);
    while (true)
    {

        if (cancelado)
        {
            cancelado = false;
            confirmado = false;
            return qtdO;
        }

        if (confirmado)
        {
            cancelado = false;
            confirmado = false;
            return indKi;
        }

        if (indKj > 2)
        {
            indKj = 2;
        }
        else if (indKj < 0)
        {
            indKj = 0;
        }

        drawSprite(150, 22, extras[1], BLACK, 1, 1, false);
        drawSprite(150, 32, numbers[indKj], BLACK, 1, 1, false);
        drawSprite(150, 37, extras[0], BLACK, 1, 1, false);

        timerOverride();
    }
    return qtdO;
}

void deckBuilder()
{
    indKi = 0;
    indKj = 0;
    cancelado = false;
    confirmado = false;

    int medKj, medKi;
    struct Carta *original = getCartasOriginal();
    struct Player player1 = getPlayer(0);
    struct Player player2 = getPlayer(1);

    drawDeckBuilderMenu(original);
    while (true)
    {
        medKi = indKi;
        medKj = indKj;

        drawSprite(185 + indKi * 45, 19 + (indKj % 4) * 46 + (indKj / 4) * screenWidth / 2, extras[2], BLACK, 1, 1, false);
        timerOverride();
        drawSprite(185 + medKi * 45, 19 + (medKj % 4) * 46 + (medKj / 4) * screenWidth / 2, extras[2], YELLOW_PAGE, 1, 1, false);

        if (cancelado)
        {
            cancelado = false;
            confirmado = false;
            return;
        }

        if (indKj > 7)
        {
            indKj = 7;
        }
        else if (indKj < 0)
        {
            indKj = 0;
        }

        if (indKi > 0)
        {
            indKi = 0;
        }
        else if (indKi < -3)
        {
            indKi = -3;
        }

        if (confirmado)
        {
            cancelado = false;
            confirmado = false;
            medKj = indKj;

            if (indKj < 4)
            {
                player1.deck[indKj + abs(indKi) * 4] = deckCardShow(original[indKj + abs(indKi) * 4], player1.deck[indKj + abs(indKi) * 4]);
            }
            else
            {
                player2.deck[indKj + abs(indKi) * 4] = deckCardShow(original[indKj + abs(indKi) * 4], player2.deck[indKj + abs(indKi) * 4]);
            }

            indKj = medKj;
            cancelado = false;
            confirmado = false;
        }
    }
}

void drawGame()
{
    struct Player atual = getPlayer(true);
    struct Player oponente = getPlayer(false);

    drawRectangle(239, 0, 10, oponente.adr, RED);
    drawRectangle(10, 0, 10, atual.adr, RED);

    for (int i = 0; i < 5; i++)
    {
        if (!oponente.livreEmJogo[i])
        {
            drawSprite(196, 12 + i * 42, spriteCartas[oponente.emJogo[i].indSprite], BLACK, 1, 1, true);
        }
        if (!atual.livreEmJogo[i])
        {
            drawSprite(76, 12 + i * 42, spriteCartas[atual.emJogo[i].indSprite], BLACK, 1, 1, true);
        }
    }
}

void drawCardArray(struct Carta *cartas, int length)
{
    drawRectangle(239, showCardsJ, 240, screenWidth - showCardsJ, YELLOW_PAGE);
    for (int i = 0; i < length; i++)
    {
        drawString(cartas[i].nome, 238 - i * 6 + 1, 231, BLACK, 1, 1);
    }
}

int showCards(struct Carta *cartas, int length)
{
    cout << "show card" << endl;
    if (length < 0)
    {
        return -1;
    }
    drawCardArray(cartas, length);

    indKi = 0;
    while (true)
    {
        timerOverride();

        if (cancelado)
        {
            while (true)
            {
                timerOverride();
                if (confirmado)
                {
                    confirmado = false;
                    cancelado = false;
                    return -1;
                }
                else if (cancelado)
                {
                    confirmado = false;
                    cancelado = false;
                    break;
                }
            }

            drawGame();
            drawCardArray(cartas, length);
        }

        if (indKi < 0)
        {
            indKi = 0;
        }
        else if (indKi >= length)
        {
            indKi = length - 1;
        }

        if (confirmado)
        {
            drawCardWithDescription(cartas[indKi]);
            while (true)
            {
                timerOverride();
                if (confirmado)
                {
                    confirmado = false;
                    cancelado = false;
                    return indKi;
                }
                else if (cancelado)
                {
                    confirmado = false;
                    cancelado = false;
                    break;
                }
            }

            drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
            drawGame();
            drawCardArray(cartas, length);
        }

        drawSprite(238 - indKi * 6 + 1, screenWidth - showCardsJ + 1, extras[0], BLACK, 1, 1, false);
        confirmado = false;
        cancelado = false;
    }
}

void drawLost()
{
    cout << "lost game" << endl;
    state = 0;
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawString("you lost", 130, screenWidth / 2 - getStringLength("you lost") / 2, BLACK, 1, 1);
    timerOverride();
    delay(2000);
}

void jumpscare(struct Carta carta)
{

    for (int i = 1; i <= carta.jumpscareSizeMultipliar; i++)
    {
        drawSprite(120 + spriteCartas[carta.indSprite].heigth * i / 2, screenWidth / 2 - spriteCartas[carta.indSprite].width * i / 2,
                   spriteCartas[carta.indSprite], carta.jumpscareColor, i, i, true);
        timerOverride();
        drawRectangle(120 + spriteCartas[carta.indSprite].heigth * i / 2, screenWidth / 2 - spriteCartas[carta.indSprite].width * i / 2,
                      spriteCartas[carta.indSprite].heigth * i, spriteCartas[carta.indSprite].width * i, YELLOW_PAGE);
        delay(500);
    }
    drawGame();
}

void drawMenu()
{
    if (indKi > 0)
    {
        indKi = 0;
    }
    else if (indKi < -2)
    {
        indKi = -2;
    }

    if (confirmado)
    {
        if (indKi == -2)
        {
            exit(0);
        }
        state = indKi + 2;
        if (state == 2)
        {
            if (!initSimulation())
            {
                state = 0;
            }
        }
    }
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawSprite(130 + 20 * indKi, screenWidth / 2 - 4 * 5, extras[0], BLACK, 1, 1, false);
    drawString("play", 130, screenWidth / 2 - getStringLength("play") / 2, BLACK, 1, 1);
    drawString("deck", 110, screenWidth / 2 - getStringLength("deck") / 2, BLACK, 1, 1);
    drawString("exit", 90, screenWidth / 2 - getStringLength("exit") / 2, BLACK, 1, 1);
    confirmado = false;
    cancelado = false;
}

void cycle()
{
    if (state == 0)
    {
        drawMenu();
    }
    else if (state == 1)
    {
        deckBuilder();
    }
    else if (state == 2)
    {
        cout << "on Game" << endl;
        if (!drawCard())
        {
            drawLost();
            return;
        }
        cout << "draw game" << endl;
        drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
        drawGame();

        while (true)
        {
            int resp = playCard();
            if (resp == 2)
            {
                break;
            }
        }

        if (checkDeath())
        {
            drawLost();
            return;
        }

        passTurn();
    }
}
