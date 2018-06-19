#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "map.h"
#include "keyandpass.h"

int kbhit(void);
void delay(void);
bool Update(Player&, Key&, PassSpot&, Map&);

#endif