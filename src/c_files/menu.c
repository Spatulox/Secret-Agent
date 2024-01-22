//
// Created by Marc on 13/01/2024.
//
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/buttons.h"
#include "../includes/global_functions.h"
#include "../includes/pressed_key.h"

void changeMenuState(int * isRunning, int * menuState, int * difficulty, SDL_Thread *audio, SDL_Point clickPoint, Button buttons[], PRESSED_KEY * key){

    if (*menuState == 0) {
        for (int i = 0; i < 3; i++) {
            if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {
                if (strcmp(buttons[i].text, "Jouer") == 0) {
                    *menuState = 1;
                    SDL_DetachThread(audio);
                    break;
                } else if (strcmp(buttons[i].text, "Parametres") == 0) {
                    *menuState = 2;
                    break;
                } else if (strcmp(buttons[i].text, "Quitter le jeu") == 0) {
                    *isRunning = 0;
                    break;
                }
            }
        }

        if (SDL_PointInRect(&clickPoint, &(buttons[11].rect))) {
            if (strcmp(buttons[11].text, "Boutique") == 0) {
                system("start https://www.amazon.fr/Noble-Collection-Minecraft-Potion-Bottle/dp/B0CJYK3MQ9/ref=sr_1_41?keywords=potion");
            }
        }

    } else if (*menuState == 1) {
        for (int i = 3; i < 6; i++) {
            if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {
                if (strcmp(buttons[i].text, "Facile") == 0) {
                    *difficulty = 1;
                    *menuState = 3;
                    SDL_DetachThread(audio);
                    break;
                } else if (strcmp(buttons[i].text, "Normal") == 0) {
                    *difficulty = 2;
                    *menuState = 3;
                    break;
                } else if (strcmp(buttons[i].text, "Difficile") == 0) {
                    *difficulty = 3;
                    *menuState = 3;
                    break;
                } else {
                    Log("Pas de bouton");
                }
            }
        }
    }
    else if (*menuState == 2){
        for (int i = 6; i < 11; i++) {
            if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))){
                SDL_Event event;
                if (strcmp(buttons[i].text, "Gauche") == 0) {
                    Log("Gauche cliqué !");
                    int quit = 0;

                    while (quit == 0) {
                        if (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quit = 1;
                                //*menuState = 0;
                            } else if (event.type == SDL_KEYDOWN) {
                                //Log("La touche pressée a le code");
                                SDL_Log("La touche pressée a le code : %d\n", event.key.keysym.sym);
                                quit = 1;
                            }
                        }
                    }


                    if(writeConfFile(3, event.key.keysym.sym, "keyNumLeft") != 0){
                        Log("ERROR : Impossible to write in the conf file");
                        break;
                    }
                    key->leftKey = event.key.keysym.sym;

                    Log("Touche écrite dans conf.txt");

                    SDL_DetachThread(audio);
                    break;
                }
                else if (strcmp(buttons[i].text, "Droite") == 0) {
                    Log("Droite cliqué !");
                    int quit = 0;

                    while (quit == 0) {
                        if (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quit = 1;
                                //*menuState = 0;
                            } else if (event.type == SDL_KEYDOWN) {
                                SDL_Log("La touche pressée a le code : %d\n", event.key.keysym.sym);
                                quit = 1;
                            }
                        }
                    }

                    if(writeConfFile(4, event.key.keysym.sym, "keyNumRight") != 0){
                        Log("ERROR : Impossible to write in the conf file");
                        break;
                    }
                    key->rightKey = event.key.keysym.sym;

                    Log("Touche écrite dans conf.txt");

                    SDL_DetachThread(audio);
                    break;
                }
                else if (strcmp(buttons[i].text, "Interagir") == 0) {
                    Log("Interagir cliqué !");

                    int quit = 0;

                    while (quit == 0) {
                        if (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                quit = 1;
                                //*menuState = 0;
                            } else if (event.type == SDL_KEYDOWN) {
                                SDL_Log("La touche pressée a le code : %d\n", event.key.keysym.sym);
                                quit = 1;
                            }
                        }
                    }

                    if(writeConfFile(5, event.key.keysym.sym, "keyNumInteract") != 0){
                        Log("ERROR : Impossible to write in the conf file");
                        break;
                    }
                    key->interactKey = event.key.keysym.sym;

                    Log("Touche écrite dans conf.txt");

                    SDL_DetachThread(audio);
                    break;
                }
                else if (strcmp(buttons[i].text, "Retour") == 0){
                    *menuState = 0;
                    Log("Retour au menu");
                }
            }
        }
    }
}