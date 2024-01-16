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
#include "src/includes/building.h"

// Structures
#include "src/includes/buttons.h"
#include "src/includes/menu.h"
#include "src/includes/player.h"
#include "src/includes/audioData.h"

#include <SDL_image.h>


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
    int lastMenuState = -1;
    int menuState = 0; // 0 => Menu principal, 1 => Menu jouer, 2 => Menu paramètres, 3 => In game
    int difficulty = 0;

    // Initialize menu
    Button buttons[6];

    // Initialize the player infos
    Player playerInfos;
    playerInfos.pathToPngFile = "./icons/player.png";

    // Initialize music
    SDL_Thread *audio = NULL;
    executeMusic(audio, &menuState);

    // Reserved the building var
    Building build;

    // Main part
    while(isRunning){

        // Render the renderer
        SDL_RenderPresent(renderer);

        // Create the buttons
        if(lastMenuState != menuState && menuState < 3){
            SDL_RenderClear(renderer);
            createMenu(window, renderer, width, height, dm, "../src/fonts/arial.ttf", buttons, &menuState);
            lastMenuState = menuState;
            Mix_HaltMusic();
        }

        if(menuState == 3 && lastMenuState != 3){
            SDL_RenderClear(renderer);
            lastMenuState = menuState;

            if(createBuilding(renderer,&difficulty, &build, &dm) != 0){
                Log("Impossible to create the building");
                destroySDL(window, renderer, NULL);
            }

            if(loadPlayer(renderer, dm, &playerInfos) != 0){
                Log("Impossible to load the player");
                destroySDL(window, renderer, NULL);
            }
        }


        // Play musics
        if (!Mix_PlayingMusic())
        {
            executeMusic(audio, &menuState);
        }

        // Listen to events
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                isRunning = 0;
            }
            // Get the mouse click
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point clickPoint = {mouseX, mouseY};
                changeMenuState(&isRunning, &menuState, &difficulty, audio, clickPoint, buttons);

            }

            // Get the keyboard click
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(menuState == 3){
                if (state[SDL_SCANCODE_W]) {
                    Log("Touche Z !");
                } else if (state[SDL_SCANCODE_S]) {
                    Log("Touche S !");
                } else if (state[SDL_SCANCODE_D]) {
                    SDL_RenderClear(renderer);
                    rightPlayer(renderer, dm, &playerInfos);
                    drawBuilding(renderer, &build, &dm, &difficulty);
                    SDL_Delay(80);
                } else if (state[SDL_SCANCODE_A]) {
                    SDL_RenderClear(renderer);
                    leftPlayer(renderer, dm, &playerInfos);
                    drawBuilding(renderer, &build, &dm, &difficulty);
                    SDL_Delay(80);
                }
            }

            // Return to the mainMenu
            if (state[SDL_SCANCODE_SEMICOLON]) {
                menuState = 0;
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