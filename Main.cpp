#include "lib/fileH/Screen.h"
#include "lib/fileH/Draw.h"
#include "simulador/simulatorH/HandlerCarta.h"

int main(int argc, char **argv){
    initSprites();
    lerCartas("atributos/cartas.txt");
    initScreen(360 , 240, 1, 1);
    startScreen(argc, argv);
    return 0;
}


