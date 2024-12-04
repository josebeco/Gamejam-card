#include "../modelos/Carta.h"
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
        original[i].nome = str;

        getline(reader, str);
        original[i].descricao = str;

        getline(reader, str);

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