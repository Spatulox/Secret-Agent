
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

char* readConfFile(int lineNum){
    FILE *fp = fopen("../cmake-build-debug/conf.txt", "r+");

    if (fp == NULL) {
        Log("Chelou mon reuf, le fichier existait avant");
        return NULL;
    }

    char lines[10][100];
    int i = 0;

    /*while (fgets(lines[i], 100, fp)) {
        if(i == lineNum){
            break;
        }
        i++;
    }
    return lines[i];*/

    while (fgets(lines, sizeof(lines), fp)) {
        if(i == lineNum){
            char *value = strchr(lines, '='); // Find the position of the equal sign
            if (value != NULL) {
                // Return the value after the equal sign (trimming any whitespace)
                fclose(fp);
                return strdup(value + 1);
            } else {
                // Handle lines without an equal sign
                fclose(fp);
                return NULL;
            }
        }
        i++;
    }
    fclose(fp);
    return NULL;
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

int getLastFloorGround(const int * window_height, const int * difficulty){
    if(window_height == NULL || difficulty == NULL){
        return -1;
    }
    int ceilBuildHeight = (int) (*window_height * 0.1);
    int downFloor = *window_height - ceilBuildHeight;
    int lastFloorGround = (downFloor / (*difficulty * 3)) + ceilBuildHeight;
    return lastFloorGround;
}

// ----------------------------------------------------------- //

int addElementToChainList(InteractivePart* newPart, InteractiveList** head) {
    InteractiveList* new = malloc(sizeof(InteractiveList));
    if (new == NULL) {
        Log("Impossible to create an element for the chain list");
        return 1;
    }

    new->interactivePart = *newPart;
    new->next = (struct InteractiveList *) *head;
    *head = new;
    //Log("Element created");
    return 0;
}

// ----------------------------------------------------------- //

void freeChainList(InteractiveList** head) {

    printInteractiveList(*head);

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
    SDL_Log("Printing chain list");
    int element = 0;
    while (list != NULL) {
        // Imprimer les détails de l'élément interactif en cours
        // SDL_Log("%d", element);
        switch (list->interactivePart.type) {
            case BUTTON:
                SDL_Log("Interactive Type: Button\n");
                break;

            case CHEST:
                SDL_Log("Interactive Type: Chest\n");
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

        displayInteractivePart(&list->interactivePart);
        // Passer à l'élément suivant dans la liste
        list = (InteractiveList *)list->next;
        element++;
    }
    SDL_Log("Printing Finished !");
}

// ----------------------------------------------------------- //

void displayInteractivePart(InteractivePart * part) {
    Doors * door;
    switch (part->type) {
        case BUTTON:
            SDL_Log("Type: InGameButton\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | Active: %d\n", part->part.button.active);
            SDL_Log(" | Position: (%d, %d)\n", part->part.button.position.x, part->part.button.position.y);
            SDL_Log(" | ActiveThing: %p\n", part->part.button.activeThing);

            InteractivePart * interPart = (InteractivePart *) part->part.button.activeThing;
            SDL_Log(" | Type: Door\n");
            SDL_Log(" |  | Address: %p\n", interPart);
            SDL_Log(" |  | Active: %d\n", interPart->part.door.active);
            SDL_Log(" |  | Position: (%d, %d)\n", interPart->part.door.position.x, interPart->part.door.position.y);
            SDL_Log(" |  | Size: (%d, %d)\n", interPart->part.door.size.width, interPart->part.door.size.height);
            break;

        case ELECTRIC_METER:
            SDL_Log("Type: ElectricMeter\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | Active: %d\n", part->part.electricMeter.active);
            SDL_Log(" | Position: (%d, %d)\n", part->part.electricMeter.position.x, part->part.electricMeter.position.y);
            SDL_Log(" | ActiveThing: %p\n", part->part.electricMeter.activeThing);
            break;

        case CODE:
            SDL_Log("Type: Code\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | Active: %d\n", part->part.code.active);
            SDL_Log(" | Position: (%d, %d)\n", part->part.code.position.x, part->part.code.position.y);
            SDL_Log(" | Code: %d\n", part->part.code.code);
            SDL_Log(" | ActiveThing: %p\n", part->part.code.activeThing);
            break;

        case LIFT:
            SDL_Log("Type: Lift\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | Active: %d\n", part->part.lift.active);
            SDL_Log(" | Position: (%d, %d)\n", part->part.lift.position.x, part->part.lift.position.y);
            break;

        case DOOR:
            SDL_Log("Type: Door\n");
            SDL_Log(" | Address global struct: %p\n", part);
            door = (Doors *) &part->part.door;
            SDL_Log(" |  | Address under struct door: %p\n", door);
            SDL_Log(" |  | Active: %d\n", door->active);
            SDL_Log(" |  | Position: (%d, %d)\n", door->position.x, door->position.y);
            SDL_Log(" |  | Size: (%d, %d)\n", door->size.width, door->size.height);
            break;

        case STAIRS:
            SDL_Log("Type: Stairs\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | UpDownStairs: %d\n", part->part.stairs.upDownStairs);
            SDL_Log(" | Position: (%d, %d)\n", part->part.stairs.position.x, part->part.stairs.position.y);
            SDL_Log(" | NextStairs: %p\n", part->part.stairs.linkStairs);
            Stairs * stairs = (Stairs *) part->part.stairs.linkStairs;
            SDL_Log("Type: Stairs\n");
            SDL_Log(" |  | UpDownStairs: %d\n", stairs->upDownStairs);
            SDL_Log(" |  | Position: (%d, %d)\n", stairs->position.x, stairs->position.y);
            break;

        case CHEST:
            SDL_Log("Type: Chest\n");
            SDL_Log(" | Address: %p\n", part);
            SDL_Log(" | Position: (%d, %d)\n", part->part.chest.position.x, part->part.chest.position.y);
            break;

        default:
            SDL_Log("Type inconnu\n");
    }
}
