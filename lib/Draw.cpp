#include "../modelos/RGB.h"
#include "../modelos/Sprite.h"
#include "fileH/Screen.h"
#include "fileH/HandlerSprites.h"
#include "../modelos/Carta.h"
#include "../modelos/Player.h"
#include "../simulador/simulatorH/jogo.h"
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
const struct RGB RED = {170, 0 ,0};

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
    numbers = readSprites("sprites/numbers.txt");
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

void drawString(string frase, int lui, int luj, struct RGB color, int width_multipliar, int heigth_multipliar)
{ // left upper corner
    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] == ' ')
        {
            luj += 3;
            continue;
        }

        drawSprite(lui, luj, alfabeto[frase[i] - 'a'], color, width_multipliar, heigth_multipliar, false);
        luj += alfabeto[frase[i] - 'a'].width + 1;
    }
}

void drawCardWithDescription(struct Carta carta)
{
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawSprite(120 + spriteCartas[carta.indSprite].width, 20, spriteCartas[carta.indSprite], carta.jumpscareColor, 2, 2, true);
}

void drawDeckBuilder()
{
    
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
    drawString("you lost", 130, screenWidth / 2 - (4 * 4), BLACK, 1, 1);
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
            initSimulation();
        }
    }
    drawRectangle(239, 0, 240, screenWidth, YELLOW_PAGE);
    drawSprite(130 + 20 * indKi, screenWidth / 2 - 4 * 5, extras[0], BLACK, 1, 1, false);
    drawString("play", 130, screenWidth / 2 - (2 * 5), BLACK, 1, 1);
    drawString("deck", 110, screenWidth / 2 - (2 * 5), BLACK, 1, 1);
    drawString("exit", 90, screenWidth / 2 - (2 * 5), BLACK, 1, 1);
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
        indKi = 0;
        indKj = 0;
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
