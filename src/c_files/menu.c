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

void changeMenuState(int * isRunning, int * menuState, int * difficulty, SDL_Thread *audio, SDL_Point clickPoint, Button buttons[]){

    if (*menuState == 0) {
        for (int i = 0; i < 3; i++) {
            if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {
                if (strcmp(buttons[i].text, "Jouer") == 0) {
                    //Log("Jouer cliqué !");
                    *menuState = 1;
                    SDL_DetachThread(audio);
                    break;
                } else if (strcmp(buttons[i].text, "Parametres") == 0) {
                    //Log("Parametres cliqué !");
                    *menuState = 2;
                    break;
                } else if (strcmp(buttons[i].text, "Quitter le jeu") == 0) {
                    //Log("Quitter cliqué !");
                    *isRunning = 0;
                    break;
                }
            }
        }
    } else if (*menuState == 1) {
        for (int i = 3; i < 6; i++) {
            if (SDL_PointInRect(&clickPoint, &(buttons[i].rect))) {
                if (strcmp(buttons[i].text, "Facile") == 0) {
                    //Log("Facile cliqué !");
                    *difficulty = 1;
                    *menuState = 3;
                    SDL_DetachThread(audio);
                    break;
                } else if (strcmp(buttons[i].text, "Normal") == 0) {
                    //Log("Normal cliqué !");
                    *difficulty = 2;
                    *menuState = 3;
                    break;
                } else if (strcmp(buttons[i].text, "Difficile") == 0) {
                    //Log("Difficile cliqué !");
                    *difficulty = 3;
                    *menuState = 3;
                    break;
                } else {
                    Log("Pas de bouton");
                }
            }
            //else{
            //    Log("Meh");
            //}
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

                    FILE *fp = fopen("../cmake-build-debug/conf.txt", "r+");

                    int key = event.key.keysym.sym;

                    int line = 0;
                    while (!feof(fp)) {
                        char buffer[100];
                        fgets(buffer, 100, fp);
                        if (strstr(buffer, "keyNumLeft") != NULL) {
                            line = ftell(fp);
                            break;
                        }
                    }

                    fseek(fp, line, SEEK_SET);

                    fprintf(fp, "%d\n", key);

                    fclose(fp);

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

                    FILE *fp = fopen("../cmake-build-debug/conf.txt", "a");

                    int key = event.key.keysym.sym;

                    fprintf(fp, "keyNumRight = %d\n", key);

                    fclose(fp);

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
                    FILE *fp = fopen("../cmake-build-debug/conf.txt", "a");

                    int key = event.key.keysym.sym;

                    fprintf(fp, "keyNumInteract = %d\n", key);

                    fclose(fp);

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