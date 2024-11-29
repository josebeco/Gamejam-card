#include <string>
#include <fstream>
#include "fileH/RGB.h"
#include "fileH/Sprite.h"
using namespace std;

const struct RGB BLACK = {0, 0, 0};
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

struct Sprite *readSprites(string fileName)
{
    string str, aux;
    int j, qtd;
    ifstream reader(fileName);

    if (!reader)
    {
        return NULL;
    }

    getline(reader, str);

    aux = "";

    for (int i = 0; i < str.length() && !isSeparator(str[i]); i++)
    {
        aux += str[i];
    }
    qtd = stoi(aux);

    struct Sprite *sprites = new struct Sprite[qtd];

    for (int c = 0; c < qtd; c++)
    {
        getline(reader, str);
        aux = "";
        for (int i = 0; i < str.length() && !isSeparator(str[i]); i++)
        {
            aux += str[i];
            j = i;
        }
        j += 2;
        sprites[c].heigth = stoi(aux);

        aux = "";
        while (j < str.length() && !isSeparator(str[j]))
        {
            aux += str[j];
            j++;
        }
        sprites[c].width = stoi(aux);

        sprites[c].pixels = new struct RGB[sprites[c].width * sprites[c].heigth];

        for (int i = 0; i < sprites[c].heigth; i++)
        {
            getline(reader, str);

            for (int j = 0; j < sprites[c].width; j++)
            {
                sprites[c].pixels[(i * sprites[c].width) + j] = (str[j] == '.') ? NONE : BLACK;
            }
        }
    }

    return sprites;
}