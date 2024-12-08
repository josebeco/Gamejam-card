#include "../../modelos/Player.h"
int getQtdCardDeck(int);
bool checkDeath();
bool drawCard();
void passTurn();
void resetDecks();
int playCard();
void embaralharCartas(struct Player&);
bool initSimulation();
struct Player& getPlayer(bool);
struct Player *getJogadores();