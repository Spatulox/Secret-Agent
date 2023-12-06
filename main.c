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
        Log("Error : Impossible to create the SDL window..");
        return 1;
    }

    /*
    if (TTF_Init() != 0){
        Log("Impossible to init ttf");
        return 1;
    }
     */

    TTF_Init();


    // Récupère la taille de l'écran
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        Log("Error when retrieving screen size");
        dm.w = 800; // Default witdh
        dm.h = 600; // Default height
    }

    // Crée une fenêtre prenant la taille de l'écran
    SDL_Window* window = SDL_CreateWindow("Secret Agent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        Log("Error when creating Secret-Agent window");
        SDL_Quit();
        return 1;
    }

    // Create the render to draw things inside the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL){
        Log("ERROR : Impossible to render the window");
        SDL_Quit();
        return 1;
    }


    int x = 0;
    int y = 0;
    int width = 200;
    int height = 200;


    // Need to create a function which create buttons
    //createRectButton();


    // Create the rectangle
    SDL_Rect rect = { x, y, width, height }; // Remplacez x, y, width et height par les coordonnées et les dimensions de votre rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Remplacez r, g, b et a par les valeurs de couleur souhaitées
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);

    // Chargez le font
    TTF_Font* font = TTF_OpenFont("src/fonts/amsterdam.ttf", 24);
    SDL_Color fg_color = {255, 255, 255};
    SDL_Color bg_color = {0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Shaded(font, "Hello, SDL!", fg_color, bg_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, &rect, NULL);

    int isRunning = 1;
    int menuGameEtc = 0; // 0 => Menu, 1 => Jouer, 2 => Paramètres

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

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();



    return 0;
}