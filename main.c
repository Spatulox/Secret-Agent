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
#include "src/includes/pressed_key.h"

#include <SDL_image.h>


int main(int argc, char** argv) {

    Log("---------------------------");
    Log("Starting Secret Agent");

    Log("Reading conf file");

    // Read the conf file or create it
    FILE *fp = fopen("conf.txt", "r");
    if (fp == NULL) {

        if(createConfFile() != 0){
            Log("Impossible to create the conf File");
        }
    }

    // Assigning value to struct
    PRESSED_KEY key;

    char * tmp = readConfFile(3);
    if(tmp == NULL){
        key.leftKey = SDLK_q;
        Log("Default value for left");
    }
    else{
        key.leftKey = atoi(tmp);
    }

    tmp = readConfFile(4);
    if(tmp == NULL){
        key.rightKey = SDLK_d;
        Log("Default value for rightkey");
    }
    else{
        key.rightKey = atoi(tmp);
    }

    tmp = readConfFile(5);
    if(tmp == NULL){
        key.interactKey = SDLK_z;
        Log("Default value for interactkey");
    }
    else{
        key.interactKey = atoi(tmp);
    }

    if (tmp != NULL){
        free(tmp);
    }


    // Initialize plein de trucs

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
    Button buttons[12];

    // Initialize the player infos
    Player playerInfos;
    playerInfos.pathToPngFile = "./icons/player.png";

    // Initialize music
    SDL_Thread *audio = NULL;

    //executeMusic(audio, &menuState); //useless
    //SDL_Delay(100);

    executeMusic(audio, &menuState);
    SDL_Delay(200);


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
                destroySDL(window, renderer, NULL);
            }

            if(createInteractive(window, &difficulty, renderer, &interactiveList) != 0){
                Log("Impossible to create the interactive parts");
                destroySDL(window, renderer, NULL);
            }
            else{
                printInteractiveList(interactiveList);
            }

            if(loadPlayer(renderer, dm, &playerInfos, &difficulty) != 0){
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

                if(menuState != 3){
                    // We are in the menu
                    changeMenuState(&isRunning, &menuState, &difficulty, audio, clickPoint, buttons, &key);
                }
                else{
                    // We are not in the menu
                    Log("Pas dans le menu");
                }

            }
            else if (event.type == SDL_KEYDOWN && menuState == 3) {

                if(event.key.keysym.sym == key.interactKey){
                    SDL_RenderClear(renderer);
                    interactWithPart(interactiveList, &playerInfos, &menuState);
                    drawBuilding(renderer, &build, &dm, &difficulty);
                    drawInteractiveParts(window, renderer, interactiveList, &difficulty);
                    drawPlayer(renderer, dm, &playerInfos);
                }
                else if(event.key.keysym.sym == key.rightKey){
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
                }
                else if(event.key.keysym.sym == key.leftKey){
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
                }
            }
            else if(event.key.keysym.sym == SDLK_m) {
                menuState = 0;
            }
            else if(event.key.keysym.sym == SDLK_r) {
                menuState = 1;
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

    Log("Exiting Secret-Agent");

    freeChainList(&interactiveList);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(icon);

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    Log("RAM of Secret-Agent full free");
    Log("Exit");
    Log("---------------------------");


    return 0;
}