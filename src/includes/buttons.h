//
// Created by M78st on 08/12/2023.
//

#ifndef BUTTONS_H
#define BUTTONS_H

#include "SDL.h"

typedef struct {
    SDL_Rect rect;
    char* text;
    int nb;
    // Autres propriétés du bouton
} Button;

#endif //BUTTONS_H
