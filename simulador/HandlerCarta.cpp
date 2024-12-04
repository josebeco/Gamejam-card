#include "../modelos/Carta.h"
#include "../modelos/RGB.h"
#include "../lib/fileH/HandlerSprites.h"
#include <string>
#include <fstream>
using namespace std;
struct Carta *original;
string r;

string inBetweenEmpty(int *ind, string str)
{
    cout << "a" << endl;
    while (isSeparator(str[(*ind)]))
    {
        (*ind)++;
    }
    string r = "";
    cout << "a" << endl;
    while ((*ind) < str.length() && !isSeparator(str[(*ind)]))
    {
        r += str[(*ind)++];
    }
    cout << "a" << endl;
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
    cout << "a" << endl;
    ifstream reader(fileName);
    if (!reader)
    {
        return;
    }
    cout << "a" << endl;
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
