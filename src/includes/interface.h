//
// Created by M78st on 06/12/2023.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include "../includes/buttons.h"

void createTextRectButton(SDL_Rect*, SDL_Window*, SDL_Renderer *, SDL_DisplayMode, int rectColorRed, int rectColorGreen, int rectColorBlue, int rectTransparency, char*, char*, SDL_Color);
void createMenu(SDL_Window *, SDL_Renderer*, int width, int height, SDL_DisplayMode, char*, Button buttons[]);
#endif //INTERFACE_H
