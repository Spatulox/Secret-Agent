//
// Created by Marc on 18/01/2024.
//

#ifndef INTERACTIVESPARTS_H
#define INTERACTIVESPARTS_H

#include "../includes/interactivesStruct.h"

int createInteractive(SDL_Window * window, const int * difficulty, SDL_Renderer * renderer, InteractiveList ** interactiveList);
void drawInteractiveParts(SDL_Window *window, SDL_Renderer * renderer, InteractiveList *list, const int * difficulty);
//int drawButtons(SDL_Window * window, SDL_Renderer * renderer, InteractivePart *part, const int * difficulty, int * buttonFloor);
//void drawElectricMetter();
//void drawCode();
//void drawLift();
//int drawDoors(SDL_Renderer * renderer, InteractivePart *part);
//int drawStairs(SDL_Renderer * renderer, InteractivePart *part);
int checkCollision(InteractiveList * interactiveList, Player * player, int leftRightPress);
void interactWithPart(InteractiveList * interactiveList, Player * player, int * menuState);

#endif //INTERACTIVESPARTS_H
