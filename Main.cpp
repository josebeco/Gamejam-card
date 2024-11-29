#include "lib/fileH/Screen.h"
#include "code/Game.h"

int main(int argc, char **argv){
    initGame();
    initScreen(320 , 240, 3, 3);
    startScreen(argc, argv);
    return 0;
}


