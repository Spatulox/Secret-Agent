//
// Created by Marc on 18/01/2024.
//

#ifndef INTERACTIVESPARTS_H
#define INTERACTIVESPARTS_H

#include "../includes/interactivesStruct.h"

int createInteractive(const int * difficulty, SDL_Renderer * renderer, InteractiveList * interactiveList);
void drawInteractiveParts();
void drawButtons();
void drawElectricMetter();
void drawCode();
void drawLift();
void drawDoors();

#endif //INTERACTIVESPARTS_H
