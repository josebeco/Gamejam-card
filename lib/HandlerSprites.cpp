#include <string>
#include <fstream>
#include "RGB.h"
using namespace std;

void readSprites(string fileName, struct RGB sprites[]){
    string size;
    ifstream reader(fileName);
    getline(reader, size);

}