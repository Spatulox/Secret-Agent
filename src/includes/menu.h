//
// Created by Marc on 13/01/2024.
//

#ifndef MAIN_C_MENU_H
#define MAIN_C_MENU_H

#include "pressed_key.h"

void changeMenuState(int * isRunning, int * menuState, int *difficulty, SDL_Thread *audio, SDL_Point clickPoint, Button buttons[], PRESSED_KEY * key);

#endif //MAIN_C_MENU_H
