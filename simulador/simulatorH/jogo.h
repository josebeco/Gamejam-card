#include "../../modelos/Player.h"
bool checkDeath();
bool drawCard();
void passTurn();
void resetDecks();
int playCard();
void embaralharCartas(struct Player&);
bool initSimulation();
struct Player& getPlayer(bool);
struct Player *getJogadores();