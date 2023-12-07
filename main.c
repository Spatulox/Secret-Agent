#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
// #include <curl/curl.h>
#include "src/includes/global_functions.h"
#include "src/includes/interface.h"



// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;
    char* text;
    int nb;
    // Autres propriétés du bouton
} Button;

// Tableau de boutons
Button buttons[3];


void createMenu(SDL_Window * window, SDL_Renderer* renderer, int width, int height, SDL_DisplayMode dm, char* fontPath) {
    buttons[0].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 3) - (height / 2), width, height - (dm.h / 30)};
    buttons[0].text = "Jouer";

    buttons[1].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 2) - (height / 2), width, height - (dm.h / 30)};
    buttons[1].text = "Parametres";

    buttons[2].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 1.5) - (height / 2), width, height - (dm.h / 30)};
    buttons[2].text = "Quitter le jeu";

    SDL_Color fColor = {0, 0, 0};
    // Dessiner les boutons sur le renderer
    for (int i = 0; i < 3; i++) {
        createTextRectButton(&buttons[i].rect, window, renderer, dm, 255, 255, 255, 255, buttons[i].text, fontPath, fColor);
    }
}






int main(int argc, char** argv) {

    Log("---------------------------");
    Log("Starting Secret Agent");

    SDL_Event event;

    // ------------Initialize SDL and SDL addons------------
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

    // ------------Retrieve screen size------------
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        Log("WARNING : Impossible to retrieve the screen size, set standard size");
        dm.w = 800; // Default witdh
        dm.h = 600; // Default height
    }

    // Create a window with the screen size
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


    // ------------Initialize the menu------------
    int width = 400;
    int height = 150;

    createMenu(window, renderer, width, height, dm, "../src/fonts/arial.ttf");


    int isRunning = 1;
    int menuGameEtc = 0; // 0 => Menu, 1 => Jouer, 2 => Paramètres


    while(isRunning){
        SDL_RenderPresent(renderer);
        // Listen to events
        if (SDL_PollEvent(&event)) {

            // Do something when event is call
            if (event.type == SDL_QUIT) {
                isRunning = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point clickPoint = {mouseX, mouseY};

                for (int i = 0; i < 3; i++) {
                    if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {
                        // Le bouton i a été cliqué
                        if (strcmp(buttons[i].text, "Jouer") == 0) {
                            Log("Jouer cliqué !");
                            isRunning = 0;
                            break;
                        } else if (strcmp(buttons[i].text, "Parametres") == 0) {
                            Log("Parametres cliqué !");
                            isRunning = 0;
                            break;
                        } else if (strcmp(buttons[i].text, "Quitter le jeu") == 0) {
                            Log("Quitter cliqué !");
                            isRunning = 0;
                            break;
                        }
                    }
                }
            }
        }

    }

    // CLear le renderer
    //SDL_RenderClear(renderer);
    // Met a jour le renderer
    //SDL_RenderPresent(renderer);


    // Wait 10  seconds
    // Log("10 seconds of delay");
    //SDL_RenderPresent(renderer);
    //SDL_Delay(10000);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();



    return 0;
}