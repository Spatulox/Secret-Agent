//
// Created by Marc on 18/01/2024.
//

#ifndef INTERACTIVESPARTS_H
#define INTERACTIVESPARTS_H

#include "../includes/interactivesStruct.h"

int createInteractive(SDL_Window * window, const int * difficulty, SDL_Renderer * renderer, InteractiveList ** interactiveList);
void drawInteractiveParts(SDL_Window *window, SDL_Renderer * renderer, InteractiveList *list, const int * difficulty);
void drawButtons(SDL_Renderer * renderer, InteractivePart *part);
void drawElectricMetter();
void drawCode();
void drawLift();
void drawDoors();
int drawStairs(SDL_Renderer * renderer, InteractivePart *part);

void interactWithPart(InteractiveList * interactiveList, Player * player, int * menuState);

#endif //INTERACTIVESPARTS_H
