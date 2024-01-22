
// Created by Marc

// global_function.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../includes/global_functions.h"
#include "../includes/interactivesStruct.h"

// ----------------------------------------------------------- //

void Log(char *string){
    // Create the time string
    time_t t = time(NULL);

    struct tm* tm;
    tm = localtime(&t);
    char date[20];
    strftime(date, 20, "%d/%m/%Y %H:%M:%S", tm);


    fflush(stdout);

    // Write the file
    FILE *file = fopen("logSecretAgent.txt", "a+");
    if (file == NULL) {
        printf("[%s] : ERROR: Unable to open the log file\n", date);
        return;
    }
    fprintf(file, "[%s] : %s\n", date, string);
    fclose(file);
    fflush(stdout);


    SDL_Log("%s, %s", string, SDL_GetError());


}

// ----------------------------------------------------------- //

int createConfFile(){
    FILE *fp = fopen("conf.txt", "w");
    if (fp == NULL) {
        Log("No conf file ?? WTF RELAUCH THE GAME");
        return 1;
    }

    // Écrire chaque ligne avec un espace réservé pour la ligne la plus longue
    int x = 10;

    fprintf(fp, "##KEYBINDS%-*s\n", x, "##");
    fprintf(fp, "#Association des touches%-*s\n\n", x,"#");
    fprintf(fp, "keyNumLeft =%-*s\n", x, "1");
    fprintf(fp, "keyNumRight =%-*s\n", x, "2");
    fprintf(fp, "keyNumInteract =%-*s\n", x, "3");

    // Fermer le fichier
    fclose(fp);
    return 0;
}

// ----------------------------------------------------------- //

int writeConfFile(int lineNum, int key, char * string){

    if( key == 114 || key == 109){
        Log("WARNING : Already use for reload / go to menu");
        return 0;
    }

    FILE *fp = fopen("../cmake-build-debug/conf.txt", "r+");

    if (fp == NULL) {
        Log("Chelou mon reuf, le fichier existait avant");
        return 1;
    }

    char lines[10][100];
    int i = 0;

    while (fgets(lines[i], 100, fp)) {
        i++;
    }

    fclose(fp);

    sprintf(lines[lineNum], "%s =%d\n", string, key);

    fp = fopen("conf.txt", "w");
    if (fp == NULL) {
        Log("Chelou mon reuf, le fichier existait avant");
        return 1;
    }

    for (int y = 0; y < i; y++) {
        fprintf(fp, "%s", lines[y]);
    }

    fclose(fp);

    return 0;
}


// ----------------------------------------------------------- //

void destroySDL(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * texture){

    if (texture != NULL){
        SDL_DestroyTexture(texture);
    }
    if (renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL){
        SDL_DestroyWindow(window);
    }

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// ----------------------------------------------------------- //

void destroySDLMusic(Mix_Music *music){

    if (music != NULL) {
        Mix_FreeMusic(music);
    }
}

// ----------------------------------------------------------- //

void inputString(char *string, int length) {
    fgets(string, length, stdin);
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';
}

// ----------------------------------------------------------- //

long getSize(char *fileName){
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
        return -1;
    long size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    return size;
}

// ----------------------------------------------------------- //
/*
int addElementToChainList(InteractivePart newPart, InteractiveList** head) {
    InteractiveList* new = malloc(sizeof(InteractiveList));
    if (newPart == NULL) {
        Log("Impossible to create an element for the chain list");
        return 1;
    }

    new->interactivePart = newPart;
    new->next = *head;
    *head = new;
    Log("Element created");
    return 0;
}*/

int addElementToChainList(InteractivePart* newPart, InteractiveList** head) {
    InteractiveList* new = malloc(sizeof(InteractiveList));
    if (new == NULL) {
        Log("Impossible to create an element for the chain list");
        return 1;
    }

    new->interactivePart = *newPart;
    new->next = (struct InteractiveList *) *head;
    *head = new; // Met à jour la tête de liste à l'extérieur de la fonction
    Log("Element created");
    return 0;
}
// ----------------------------------------------------------- //

void freeChainList(InteractiveList** head) {

    //printInteractiveList(*head);

    InteractiveList* curr = *head;
    InteractiveList* next;

    while (curr != NULL) {
        next = (InteractiveList *) curr->next;
        free(curr);
        curr = next;
    }

    *head = NULL;
    Log("Chain list full free");
}

// ----------------------------------------------------------- //

void printInteractiveList(InteractiveList *list) {
    Log("Printing chain list");
    int element = 0;
    while (list != NULL) {
        // Imprimer les détails de l'élément interactif en cours
        // SDL_Log("%d", element);
        switch (list->interactivePart.type) {
            case BUTTON:
                SDL_Log("Interactive Type: Button\n");
                break;

            case STAIRS:
                SDL_Log("Interactive Type: Stairs\n");
                break;

            case CODE:
                SDL_Log("Interactive Type: Code\n");
                break;

            case LIFT:
                SDL_Log("Interactive Type: Lift\n");
                break;

            case DOOR:
                SDL_Log("Interactive Type: Door\n");
                break;

            case ELECTRIC_METER:
                SDL_Log("Interactive Type: Electric Meter\n");
                break;

            default:
                SDL_Log("Interactive Type: Unknown\n");
        }
        // Passer à l'élément suivant dans la liste
        list = (InteractiveList *)list->next;
        element++;
    }
    Log("Printing Finished !");
}