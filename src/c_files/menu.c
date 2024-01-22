//
// Created by Marc on 13/01/2024.
//
#include <SDL.h>
#include <SDL_mixer.h>

#include "../includes/buttons.h"
#include "../includes/global_functions.h"

void changeMenuState(int * isRunning, int * menuState, int * difficulty, SDL_Thread *audio, SDL_Point clickPoint, Button buttons[]){

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
}