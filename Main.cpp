#include "lib/fileH/Screen.h"
#include "lib/fileH/Draw.h"
#include "simulador/simulatorH/HandlerCarta.h"

int main(int argc, char **argv){
    initSprites();
    lerCartas("atributos/cartas.txt");
    initScreen(360 , 240, 3, 3);
    startScreen(argc, argv);
    return 0;
}


