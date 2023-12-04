#include <stdio.h>
#include <SDL.h>
#include "src/includes/global_functions.h"

int main(int argc, char** argv) {

    Log("---------------------------");
    Log("Starting Secret Agent");



    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Log("Error : Impossible to create the SDL window..");
        return 1;
    }



    // Récupère la taille de l'écran
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        SDL_Log("Error when retrieving screen size");
        dm.w = 800; // Default witdh
        dm.h = 600; // Default height
    }

    // Crée une fenêtre prenant la taille de l'écran
    SDL_Window* window = SDL_CreateWindow("Secret Agent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_Log("Error when creating Secret-Agent window");
        return 1;
    }

    // Wait 10  seconds
    SDL_Delay(10000);


    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}