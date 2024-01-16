//
// Created by M78st on 16/01/2024.
//
#include <SDL.h>

#include "../includes/building.h"
#include "../includes/global_functions.h"

#include "../includes/lines.h"
#include "../includes/structPlayer.h"


void placeInteractiveParts(){

}

int createBuilding(SDL_Renderer * renderer, const int * difficulty, Building * Build, const SDL_DisplayMode * dm)
{
    //SDL_Log("%d", dm->w);
    Log("Creating Building");
    double x1= (dm->w)*0.1;
    double x2= (dm->w)-x1;

    double y1= (dm->h)*0.1;
    double y2= dm->h;

    Lines leftWall;
    leftWall.x1 = x2;
    leftWall.y1 = y1;
    leftWall.x2 = x2;
    leftWall.y2 = y2;

    Lines rightWall;
    rightWall.x1 = x1;
    rightWall.y1 = y1;
    rightWall.x2 = x1;
    rightWall.y2 = y2;

    Build->rightWall = rightWall;
    Build->leftWall = leftWall;

    drawBuilding(renderer, Build, dm, difficulty);
    return 0;
}

void drawBuilding(SDL_Renderer * renderer, Building * Build, const SDL_DisplayMode * dm, const int * difficulty){
    //Log("Drawing Building");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw walls
    SDL_RenderDrawLine(renderer, Build->rightWall.x1, Build->rightWall.y1, Build->rightWall.x1, Build->rightWall.y2);
    SDL_RenderDrawLine(renderer, Build->leftWall.x1, Build->leftWall.y1, Build->leftWall.x1, Build->leftWall.y2);

    // Drawn ceil
    SDL_RenderDrawLine(renderer, Build->rightWall.x1, Build->rightWall.y1, Build->leftWall.x1, Build->leftWall.y1);

    // Drawn floors
    double baseDmHeight = dm->h*0.1;
    int deltaBaseCeil = Build->rightWall.y2 - Build->rightWall.y1;
    SDL_Log("DeltaBaseCeil : %d", deltaBaseCeil);

    int maxI = *difficulty * 3;
    for (int i = 1; i < maxI; ++i) {
        SDL_RenderDrawLine(renderer, Build->rightWall.x1, baseDmHeight + ((deltaBaseCeil / (maxI)) * i), Build->leftWall.x1, baseDmHeight + ((deltaBaseCeil / (maxI)) * i));
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}