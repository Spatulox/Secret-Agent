//
// Created by Marc on 13/01/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "../includes/structPlayer.h"

int loadPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player, const int * difficulty);
void rightPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player);
int drawPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player);
void leftPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player);

#endif //PLAYER_H
