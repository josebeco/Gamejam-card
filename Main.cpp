#include "code/Screen.h"
#include "code/lib/Game.h"

int main(int argc, char **argv){
    initGame();
    initScreen(320 , 240, 3, 3);
    startScreen(argc, argv);
    return 0;
}


