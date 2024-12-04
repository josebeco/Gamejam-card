#include "../modelos/Carta.h"
#include "../modelos/RGB.h"
#include "../lib/fileH/HandlerSprites.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Carta *original;
string r;

void imprirmirCarta(struct Carta c){
    cout << c.nome << endl;
    cout << c.descricao << endl;
    cout << c.mascara << endl;
    cout << c.ambiente << endl;
    cout << c.item << endl;
    cout << c.indFuncPutInPlay << endl;
    cout << c.indFuncInPlay << endl;
}

string inBetweenEmpty(int *ind, string str)
{
  
    while (isSeparator(str[(*ind)]))
    {
        (*ind)++;
    }
    string r = "";

    while ((*ind) < str.length() && !isSeparator(str[(*ind)]))
    {
        r += str[(*ind)++];
    }
   
    return r;
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
    if (!reader)
    {
        return;
    }

    string str, aux;
    int qtd;
    int ind = 0;
    int *indP = &ind;

    getline(reader, str);
    aux = inBetweenEmpty(indP, str);
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

        aux = inBetweenEmpty(indP, str);
        original[i].mascara = stoi(aux) == 1;

        aux = inBetweenEmpty(indP, str);
        original[i].ambiente = stoi(aux) == 1;

        aux = inBetweenEmpty(indP, str);
        original[i].item = stoi(aux) == 1;

        getline(reader, str);
        ind = 0;

        aux = inBetweenEmpty(indP, str);
        original[i].indFuncPutInPlay = stoi(aux);

        aux = inBetweenEmpty(indP, str);
        original[i].indFuncInPlay = stoi(aux);

        getline(reader, str);
        ind = 0;

        aux = inBetweenEmpty(indP, str);
        original[i].indSprite = stoi(aux);

        getline(reader, str);
        ind = 0;

        aux = inBetweenEmpty(indP, str);
        original[i].jumpscareColor.r = stoi(aux);

        aux = inBetweenEmpty(indP, str);
        original[i].jumpscareColor.g = stoi(aux);

        aux = inBetweenEmpty(indP, str);
        original[i].jumpscareColor.b = stoi(aux);

        getline(reader, str);
        ind = 0;
        aux = inBetweenEmpty(indP, str);
        original[i].jumpscareSizeMultipliar = stoi(aux);

        getline(reader, str);
        ind = 0;

        for (int j = 0; j < 10; j++)
        {
            aux = inBetweenEmpty(indP, str);
            original[i].values[j] = stoi(aux);
        }
        imprirmirCarta(original[i]);
    }
}

struct Carta copiarCarta(int ind)
{
    struct Carta carta;
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
    return carta;
}
