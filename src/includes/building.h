//
// Created by Marc on 16/01/2024.
//

#ifndef BUILDING_H
#define BUILDING_H

#include "./lines.h"
#include "./structPlayer.h"

typedef struct {
    Lines leftWall;
    Lines rightWall;
} Building;

void placeInteractiveParts();
int createBuilding(SDL_Renderer * renderer, const int * difficulty,  Building * Build, const SDL_DisplayMode *dm);
void drawBuilding(SDL_Renderer * renderer, Building * build, const SDL_DisplayMode * dm, const int * difficulty);
#endif //BUILDING_H
