#include "../modelos/Carta.h"
#include "../modelos/RGB.h"
#include <string>
#include <fstream>
using namespace std;
struct Carta *original;

bool isSeparator(char c)
{
    return c == ' ' || c == '\n' || c == '\0';
}

bool isEmpty(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isSeparator(str[i]))
        {
            return false;
        }
    }
    return true;
}

int inBetweenEmpty(int ind, string str, string r)
{
    while (isSeparator(str[ind]))
    {
        ind++;
    }

    string r = "";

    while (ind < str.length() && !isSeparator(str[ind]))
    {
        r += str[ind++];
    }
    return ind;
}

string cleanString(string str)
{
    string r = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '\n' || str[i] == '\0')
        {
            continue;
        }

        r += str[i];
    }
    return r;
}

void lerCartas(string fileName)
{
    ifstream reader(fileName);
    string str, aux;
    int qtd, ind = 0;
    getline(reader, str);

    ind = inBetweenEmpty(ind, str, aux);
    qtd = stoi(aux);

    original = new struct Carta[qtd];
    for (int i = 0; i < qtd; i++)
    {
        original[i].id = i;

        getline(reader, str);
        original[i].nome = cleanString(str);

        getline(reader, str);
        original[i].descricao = cleanString(str);

        getline(reader, str);
        ind = 0;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].mascara = stoi(aux) == 1;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].ambiente = stoi(aux) == 1;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].item = stoi(aux) == 1;

        getline(reader, str);
        ind = 0;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].indFuncPutInPlay = stoi(aux);

        ind = inBetweenEmpty(ind, str, aux);
        original[i].indFuncInPlay = stoi(aux);

        getline(reader, str);
        ind = 0;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].indSprite = stoi(aux);

        getline(reader, str);
        ind = 0;

        ind = inBetweenEmpty(ind, str, aux);
        original[i].jumpscareColor.r = stoi(aux);

        ind = inBetweenEmpty(ind, str, aux);
        original[i].jumpscareColor.g = stoi(aux);

        ind = inBetweenEmpty(ind, str, aux);
        original[i].jumpscareColor.b = stoi(aux);

        getline(reader, str);
        ind = 0;

        original[i].jumpscareSizeMultipliar = stoi(aux);

        getline(reader, str);
        ind = 0;

        for (int j = 0; j < 10; j++)
        {
            ind = inBetweenEmpty(ind, str, aux);
            original[i].values[j] = stoi(aux);
        }
    }
}

void copiarCarta(struct Carta carta, int ind)
{
    carta.id = original[ind].id;

    carta.mascara = original[ind].mascara;
    carta.ambiente = original[ind].ambiente;
    carta.item = original[ind].item;

    carta.nome = original[ind].nome;
    carta.descricao = original[ind].descricao;

    carta.turnosRestantes = original[ind].turnosRestantes;

    carta.indFuncInPlay = original[ind].indFuncInPlay;
    carta.indFuncPutInPlay = original[ind].indFuncPutInPlay;
    carta.indSprite = original[ind].indSprite;

    carta.jumpscareColor = original[ind].jumpscareColor;
    carta.jumpscareSizeMultipliar = original[ind].jumpscareSizeMultipliar;

    for (int i = 0; i < 10; i++)
    {
        carta.values[i] = original[ind].values[i];
    }

    carta.nula = original[ind].nula;
}