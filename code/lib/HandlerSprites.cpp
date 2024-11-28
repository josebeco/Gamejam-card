#include <string>
#include <fstream>
#include "RGB.h"
#include <iostream>
using namespace std;

const struct RGB BLACK = {255, 255, 255};
const struct RGB NONE = {-1, -1, -1};

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

void readSprites(string fileName, struct RGB sprites[])
{
    string str, aux;
    int j, height, witdh, qtd;
    ifstream reader(fileName);

    if (!reader)
    {
        cerr << "Could not open the file!" << endl;
    }

    getline(reader, str);
    cout << str << endl;
    aux = "";
    for (int i = 0; i < str.length() && !isSeparator(str[i]); i++)
    {
        aux += str[i];
        j = i;
    }
    j += 2;
    height = stoi(aux);

    aux = "";
    while (j < str.length() && !isSeparator(str[j]))
    {
        aux += str[j];
        j++;
    }

    witdh = stoi(aux);

    aux = "";
    
    while (++j < str.length() && !isSeparator(str[j]))
    {

        aux += str[j];
    }
 
    qtd = stoi(aux);

    sprites = new struct RGB[qtd * witdh * height];

    for (int i = 0; getline(reader, str); i++)
    {
        if (isEmpty(str))
        {
            i--;
            continue;
        }

        for (int j = 0; j < witdh; j++)
        {
            sprites[(i * witdh) + j] = (str[j] == '.') ? NONE : BLACK;
        }
    }
}