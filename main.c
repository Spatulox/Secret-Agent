#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>
// #include <curl/curl.h>

// Functions
#include "src/includes/global_functions.h"
#include "src/includes/interface.h"
#include "src/includes/musics.h"

// Structures
#include "src/includes/buttons.h"
#include "src/includes/audioData.h"


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

    // Create the windows icon

    SDL_Surface* icon = SDL_LoadBMP("./icons/icon.bmp");
    if (icon == NULL){
        Log("ERROR : Impossible to create the icon of the game");
    }
    SDL_SetWindowIcon(window, icon);




    // ------------Initialize the menu------------
    int width = 400;
    int height = 150;

    // Initialize menu state
    int isRunning = 1;
    int lastMenuState = 0;
    int coucou = 0;
    int menuState = 0; // 0 => Menu principal, 1 => Menu jouer, 2 => Menu paramètres
    /*menuState = &coucou;
    SDL_Log("%d", *menuState);*/

    // Initialize menu
    Button buttons[3];
    createMenu(window, renderer, width, height, dm, "../src/fonts/arial.ttf", buttons);

    // Initialize music
    SDL_Thread *audio = NULL;
    SDL_Delay(100);

    executeMusic(audio, &menuState);

    // Main part
    while(isRunning){
        // Render the renderer
        SDL_RenderPresent(renderer);

        /*if(lastMenuState != menuState && menuState < 3){
            SDL_RenderClear(renderer);
            //createMenu(window, renderer, width, height, dm, "../src/fonts/arial.ttf", buttons);
        }*/

        if (!Mix_PlayingMusic())
        {
            SDL_Delay(100);
            executeMusic(audio, &menuState);
        }

        // Listen to events
        if (SDL_PollEvent(&event)) {

            // Do something when event is call
            if (event.type == SDL_QUIT) {
                isRunning = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point clickPoint = {mouseX, mouseY};

                if (menuState == 0) {
                    for (int i = 0; i < 3; i++) {
                        if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {

                            if (strcmp(buttons[i].text, "Jouer") == 0) {
                                Log("Jouer cliqué !");
                                menuState = 1;
                                SDL_DetachThread(audio);
                                Mix_HaltMusic();
                                break;
                            } else if (strcmp(buttons[i].text, "Parametres") == 0) {
                                Log("Parametres cliqué !");
                                isRunning = 1;
                                menuState = 2;
                                Mix_HaltMusic();
                                SDL_Delay(500);
                                break;
                            } else if (strcmp(buttons[i].text, "Quitter le jeu") == 0) {
                                Log("Quitter cliqué !");
                                isRunning = 0;
                                Mix_HaltMusic();
                                break;
                            }
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
    SDL_FreeSurface(icon);

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();



    return 0;
}