#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
// #include <curl/curl.h>
#include "src/includes/global_functions.h"
#include "src/includes/interface.h"

int main(int argc, char** argv) {

    SDL_Event event;

    Log("---------------------------");
    Log("Starting Secret Agent");



    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Log("ERROR : Impossible to initialize SDL");
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0){
        Log("ERROR : Impossible to initialize SDL_TTF");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    // Récupère la taille de l'écran
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        Log("WARNING : Impossible to retrieve the screen size, set standard size");
        dm.w = 800; // Default witdh
        dm.h = 600; // Default height
    }

    // Crée une fenêtre prenant la taille de l'écran
    SDL_Window* window = SDL_CreateWindow("Secret Agent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        Log("ERROR : Impossible to create the Secret-Agent window");
        destroySDL(NULL, NULL, NULL);
    }

    // Create the render to draw things inside the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        Log("ERROR : Impossible to render the window");
        destroySDL(window, renderer, NULL);
    }



    int width = 400;
    int height = 150;

    // Need to create a function which create buttons
    //createTextRectButton(renderer, float x, float y, float width, float height, font, textColor);
    //SDL_Rect rect = { (dm.w/2)-(width/2), (dm.h/2)-(height/2), width, height };
    //createTextRectButton(SDL_Rect*, SDL_Window*, SDL_Renderer *, SDL_DisplayMode, int rectColorRed, int rectColorGreen, int rectColorBlue, int rectTransparency, TTF_Font*, SDL_Color);


    // Create the rectangle
    SDL_Rect rect = { (dm.w/2)-(width/2), (dm.h/4)-(height/2), width, height }; // Remplacez x, y, width et height par les coordonnées et les dimensions de votre rectangle
    SDL_Color fColor = {0, 255, 0};
    createTextRectButton(&rect, window, renderer, dm, 0, 0, 255, 255, "Hello SDL PUTAIN", "../src/fonts/arial.ttf", fColor);


    int isRunning = 1;
    int menuGameEtc = 0; // 0 => Menu, 1 => Jouer, 2 => Paramètres

    // Boucle du jeu
//    SDL_RenderPresent(renderer);
//    SDL_Delay(10000);

//    destroySDL(window, renderer, texture);

    while (isRunning) {
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                isRunning = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point clickPoint = {mouseX, mouseY};
                if (SDL_PointInRect(&clickPoint, &rect)) {
                    Log("Cliqué !");
                    isRunning = 0;
                }
            }
        }

    }

    // Wait 10  seconds
    //SDL_Delay(10000);

    //SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();



    return 0;
}