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
#include "src/includes/interactivesParts.h"

// Structures
#include "src/includes/buttons.h"
#include "src/includes/menu.h"
#include "src/includes/player.h"
#include "src/includes/audioData.h"
#include "src/includes/interactivesStruct.h"

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
    //executeMusic(audio, &menuState); //useless
    //SDL_Delay(100);

    // Reserved the building var
    Building build;

    // Reserve the InteractivesPart
    InteractiveList * interactiveList = NULL;

    // Main part
    while(isRunning){

        // Render the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

        // Create the menu
        if(lastMenuState != menuState && menuState < 3){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            createMenu(window, renderer, width, height, dm, "./fonts/arial.ttf", buttons, &menuState);
            lastMenuState = menuState;
            executeMusic(audio, &menuState);
        }

        // Create the building and load the player
        if(menuState == 3 && lastMenuState != 3){
            SDL_RenderClear(renderer);
            Mix_HaltMusic();
            lastMenuState = menuState;

            if(createBuilding(renderer,&difficulty, &build, &dm) != 0){
                Log("Impossible to create the building");
                menuState = 0;
                //destroySDL(window, renderer, NULL);
            }
            else{
                Log("Building successfully loaded !");
                //printInteractiveList(interactiveList);
            }

            if(createInteractive(window, &difficulty, renderer, &interactiveList) != 0){
                Log("Impossible to create the interactive parts");
                menuState = 0;
                //destroySDL(window, renderer, NULL);
            }
            else{
                Log("Interactive part successfully loaded !");
                //printInteractiveList(interactiveList);
            }

            if(loadPlayer(renderer, dm, &playerInfos, &difficulty) != 0){
                Log("Impossible to load the player");
                menuState = 0;
                //destroySDL(window, renderer, NULL);
            }
            else{
                Log("Player successfully loaded !");
                //printInteractiveList(interactiveList);
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

                if(menuState != 3){
                    // We are in the menu
                    changeMenuState(&isRunning, &menuState, &difficulty, audio, clickPoint, buttons);
                }
                else{
                    // We are not in the menu
                    Log("Pas dans le menu");
                }

            }
            else if (event.type == SDL_KEYDOWN && menuState == 3) {
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        SDL_RenderClear(renderer);
                        interactWithPart(interactiveList, &playerInfos, &menuState);
                        if(menuState != 3){
                            break;
                        }
                        drawBuilding(renderer, &build, &dm, &difficulty);
                        drawInteractiveParts(window, renderer, interactiveList, &difficulty);
                        drawPlayer(renderer, dm, &playerInfos);
                        //Log("Touche Z !");
                        break;

                    case SDLK_s:

                        break;

                    case SDLK_d:
                        SDL_RenderClear(renderer);
                        drawBuilding(renderer, &build, &dm, &difficulty);
                        drawInteractiveParts(window, renderer, interactiveList, &difficulty);
                        if(checkCollision(interactiveList, &playerInfos, 1) == 0) {
                            rightPlayer(renderer, dm, &playerInfos);
                        }
                        else{
                            drawPlayer(renderer, dm, &playerInfos);
                        }
                        SDL_Delay(70);
                        break;

                    case SDLK_q:
                        SDL_RenderClear(renderer);
                        drawBuilding(renderer, &build, &dm, &difficulty);
                        drawInteractiveParts(window, renderer, interactiveList, &difficulty);
                        if(checkCollision(interactiveList, &playerInfos, 0) == 0){
                            leftPlayer(renderer, dm, &playerInfos);
                        }
                        else{
                            drawPlayer(renderer, dm, &playerInfos);
                        }
                        SDL_Delay(70);
                        break;

                    default:
                        break;
                }
            }
            else{
                switch (event.key.keysym.sym) {
                    case SDLK_m:
                        menuState = 0;
                        break;
                    case SDLK_r:
                        menuState = 1;
                        break;
                    default:
                        break;
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

    freeChainList(&interactiveList);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(icon);

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();



    return 0;
}