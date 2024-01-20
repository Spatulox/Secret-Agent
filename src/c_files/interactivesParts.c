//
// Created by Marc on 18/01/2024.
//
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>

#include "../includes/interactivesStruct.h"
#include "../includes/global_functions.h"

#include "../includes/interactivesParts.h"
#include "../includes/structPlayer.h"

// Global Var //
SDL_Surface* imageSurfaceUpStairs = NULL;
SDL_Surface* imageSurfaceDownStairs = NULL;
SDL_Surface* imageChest = NULL;




// ------------ CREATE FUNCTIONS ------------ //

int createStairs(SDL_Window *window, const int * difficulty, InteractiveList ** interactiveList, int i){
    InteractivePart * partUpStairs = malloc(sizeof(InteractivePart));

    if(partUpStairs == NULL){
        Log("Impossible to reserve the data");
        freeChainList(interactiveList);
        return 1;
    }

    InteractivePart * partDownStairs = malloc(sizeof(InteractivePart));

    if(partDownStairs == NULL){
        Log("Impossible to reserve the data");
        freeChainList(interactiveList);
        return 1;
    }

    // Take the width / height of the window
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    //int random_number = rand() % (window_width + 1);
    int max = window_width - window_width * 0.3;
    int min = 0 + window_width * 0.2;
    int random_number = min + rand() % (max - min + 1);

    // Height of the building ceiling
    double baseDmHeight = window_height*0.1;
    int deltaBaseCeil = window_height - baseDmHeight;

    // Determine automatic position of the stairs
    // Determine the number of floors
    int maxI = *difficulty * 3;

    // Super scientist calcul to determine the y of the floor of the building.
    //(int) baseDmHeight + ((deltaBaseCeil / (maxI)) * (i))
    // We add +1 to i because i begin at 0.

    int heightOfFloorDownS = (int) baseDmHeight + ((deltaBaseCeil / (maxI)) * (i+2));
    int heightOfFloorUpS = (int) baseDmHeight + ((deltaBaseCeil / (maxI)) * (i+1));
    //SDL_Log("%d", heightOfFloorDownS);
    int heightOfStairs = (int) baseDmHeight + ((deltaBaseCeil / (maxI)) * (i+3)) - heightOfFloorDownS;
    //SDL_Log("%d", heightOfStairs);


    // Create the upstairs (up)
    partUpStairs->type = STAIRS;
    partUpStairs->part.stairs.upDownStairs = 1;
    partUpStairs->part.stairs.linkStairs = 0;

    // Create the downstairs (down)
    partDownStairs->type = STAIRS;
    partDownStairs->part.stairs.upDownStairs = 0;
    partDownStairs->part.stairs.linkStairs = 0;

    // Determine position
    // up stair
    partUpStairs->part.stairs.position.x = random_number;
    partUpStairs->part.stairs.position.y = heightOfFloorUpS-heightOfStairs;
    //partUpStairs->part.stairs.size.width = random_number;
    partUpStairs->part.stairs.size.height = heightOfStairs;

    // down stair
    partDownStairs->part.stairs.position.x = random_number;
    partDownStairs->part.stairs.position.y = heightOfFloorDownS-heightOfStairs;

    //part->part.stairs.position.y-part->part.stairs.size.height;

    //partDownStairs->part.stairs.size.width = random_number;
    partDownStairs->part.stairs.size.height = heightOfStairs;

    // Link the two stairs
    partUpStairs->part.stairs.linkStairs = (struct Stairs *) &partDownStairs->part.stairs;
    partDownStairs->part.stairs.linkStairs = (struct Stairs *) &partUpStairs->part.stairs;


    // Retrieve infos from the pointer inside the struct of the first stairs
    //Stairs * tmp = (Stairs *) partDownStairs->part.stairs.linkStairs;
    //SDL_Log("part up stairs struct %d", tmp->upDownStairs);
    //SDL_Log("part down stairs %p", &partDownStairs);
    //SDL_Log("part down stairs struct%p", &partDownStairs->part.stairs);

    //SDL_Log("%d", *partUpStairs->part.stairs.linkStairs);


    addElementToChainList(partUpStairs, interactiveList);
    addElementToChainList(partDownStairs, interactiveList);
}

// ------------------------------------------ //

int createChest(SDL_Window *window, InteractiveList ** interactiveList, const int * difficulty){
    InteractivePart * chest = malloc(sizeof(InteractivePart));

    if(chest == NULL){
        Log("Impossible to reserve the data");
        freeChainList(interactiveList);
        return 1;
    }

    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    int max = (int) (window_width - (window_width * 0.10));

    int ceilBuildHeight = (int) (window_height*0.1);
    int totalBuildingHeight = window_height - ceilBuildHeight;
    int lastFloor = (totalBuildingHeight/ (*difficulty*3)) + ceilBuildHeight;

    chest->type = CHEST;
    chest->part.chest.position.x = 0;
    chest->part.chest.position.y = 0;
    chest->part.chest.size.height = 0;
    chest->part.chest.size.width = 0;

    addElementToChainList(chest, interactiveList);
}

// ------------------------------------------ //

int createInteractive(SDL_Window *window, const int * difficulty, SDL_Renderer * renderer, InteractiveList ** interactiveList){

    if(imageSurfaceDownStairs == NULL){
        imageSurfaceUpStairs = IMG_Load("./icons/upStairs.png");
        imageSurfaceDownStairs = IMG_Load("./icons/downStairs.png");
        imageChest = IMG_Load("./icons/chest.png");

    }

    if(interactiveList == NULL){
        Log("Interactive List null");
        return 1;
    }

    if(*interactiveList != NULL){
        Log("Refreshing Interactiv list");
        freeChainList(interactiveList);
    }

    for (int i = 0; i < ((*difficulty)*3)-1; ++i) {

        // ------- Stairs ------- //

        createStairs(window, difficulty, interactiveList, i);

        // ------- Buttons ------- //

    }
    //printInteractiveList(interactiveList);
    drawInteractiveParts(window, renderer, *interactiveList, difficulty);

    return 0;
}





// ------------ DRAW FUNCTIONS ------------ //

void drawButtons(SDL_Renderer * renderer, InteractivePart *part){

}


int drawChest(SDL_Window *window, SDL_Renderer *renderer, const int * difficulty, InteractivePart *part) {

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageChest);
    if(imageTexture == NULL){
        return 1;
    }

    if(part->part.chest.size.width == 0) {

        int imageWidth;
        int imageHeight;
        SDL_QueryTexture(imageTexture, NULL, NULL, &imageWidth, &imageHeight);


        imageWidth = imageWidth / (*difficulty + 2);
        imageHeight = imageHeight / (*difficulty + 2);

        part->part.chest.size.width = imageWidth;
        part->part.chest.size.height = imageHeight;


        int window_width;
        int window_height;

        SDL_GetWindowSize(window, &window_width, &window_height);
        int max = (int) (window_width - (window_width * 0.10));

        int ceilBuildHeight = (int) (window_height * 0.1);
        int totalBuildingHeight = window_height - ceilBuildHeight;
        int lastFloor = (totalBuildingHeight / (*difficulty * 3)) + ceilBuildHeight;

        part->part.chest.position.x =  max-imageWidth;
        part->part.chest.position.y = lastFloor-imageHeight;
    }

    SDL_Rect dstRect;
    dstRect.w = part->part.chest.size.width;
    dstRect.h = part->part.chest.size.height;
    dstRect.x =  part->part.chest.position.x;
    dstRect.y =  part->part.chest.position.y;

    SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);
}


// ------------------------------------------------ //

void drawElectricMetter(){

}

// ------------------------------------------------ //

void drawCode(){

}

// ------------------------------------------------ //

void drawLift(){

}

// ------------------------------------------------ //

void drawDoors(){

}

// ------------------------------------------------ //

int drawStairs(SDL_Renderer * renderer, InteractivePart *part){

    SDL_Surface* imageSurface = NULL;

    if(part->part.stairs.upDownStairs == 1){
        imageSurface = imageSurfaceUpStairs;
    }
    else{
        imageSurface = imageSurfaceDownStairs;
    }

    if(imageSurface == NULL){
        Log("Impossible to load the stair texture");
        return 1;
    }

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(imageTexture == NULL){
        return 1;
    }

    int imageWidth;
    int imageHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &imageWidth, &imageHeight);

    SDL_Rect dstRect;
    dstRect.w = imageWidth;
    dstRect.h = part->part.stairs.size.height;

    part->part.stairs.size.width = imageWidth;
    dstRect.x = part->part.stairs.position.x;
    dstRect.y = part->part.stairs.position.y;

    SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

}

// ------------------------------------------------ //

void drawInteractiveParts(SDL_Window *window, SDL_Renderer * renderer, InteractiveList *list, const int * difficulty){

    Log("drawInteractiveParts");
    int element;
    while (list != NULL) {
        // Imprimer les détails de l'élément interactif en cours
        //SDL_Log("%d", element);
        switch (list->interactivePart.type) {
            case BUTTON:
                SDL_Log("Interactive Type: Button\n");
                drawButtons(renderer, &list->interactivePart);
                break;

            case STAIRS:
                //SDL_Log("Interactive Type: Stairs\n");
                drawStairs(renderer, &list->interactivePart);
                break;

            case CODE:
                SDL_Log("Interactive Type: Code\n");
                break;

            case LIFT:
                SDL_Log("Interactive Type: Lift\n");
                break;

            case DOOR:
                SDL_Log("Interactive Type: Door\n");
                drawDoors(renderer, &list->interactivePart);
                break;

            case ELECTRIC_METER:
                SDL_Log("Interactive Type: Electric Meter\n");
                break;

            case CHEST:
                SDL_Log("Interactive Type: Chest\n");
                drawChest(window, renderer, difficulty, &list->interactivePart);
                break;

            default:
                SDL_Log("Interactive Type: Unknown\n");
        }
        // Passer à l'élément suivant dans la liste
        list = (InteractiveList *)list->next;
        element++;
    }


}

// ------------------------------------------------ //

void interactWithPart(InteractiveList * interactiveList, Player * player, int * menuState){
    int min;
    int max;
    int partX;
    int partY;
    int thingHeight;

    // Var to avoid multiple floor change
    int changeFloor = 0;

    if(interactiveList == NULL){
        Log("No chain list :/");
    }
    while (interactiveList != NULL){
        switch (interactiveList->interactivePart.type) {
            case BUTTON:
                                SDL_Log("Interactive Type: Button\n");
                break;

            case STAIRS:

                // Calcul x of the stairs
                partX = interactiveList->interactivePart.part.stairs.position.x;
                partY = interactiveList->interactivePart.part.stairs.position.y;
                max = partX + (interactiveList->interactivePart.part.stairs.size.width - interactiveList->interactivePart.part.stairs.size.width*0.5);
                min = partX - (interactiveList->interactivePart.part.stairs.size.width*0.2 + interactiveList->interactivePart.part.stairs.size.width*0.2);

                // Delta
                // Take the y of the stair + size y of the stair - height of the player to compare the result with the y of the player
                thingHeight = interactiveList->interactivePart.part.stairs.size.height;
                int tmp = (int)(thingHeight + partY) - player->size.height;

                // Next to a stair
                // check x of the stair and player
                // check the y of the player and the stairs
                if(player->coordinates.x >= min && player->coordinates.x <= max && tmp == player->coordinates.y){

                    Stairs * nextStairs = (Stairs *) interactiveList->interactivePart.part.stairs.linkStairs;

                    if(changeFloor == 0 && interactiveList->interactivePart.part.stairs.upDownStairs == 0){
                        player->coordinates.y = partY - player->size.height;
                        changeFloor = 1;
                    }
                    else if(changeFloor == 0 && interactiveList->interactivePart.part.stairs.upDownStairs == 1){
                        player->coordinates.y = nextStairs->position.y + (nextStairs->size.height - player->size.height);
                        changeFloor = 1;
                    }

                }

                //SDL_Log("Interactive Type: Stairs\n");
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

            case CHEST:
                SDL_Log("Interactive Type: Chest\n");
                Chest chest = interactiveList->interactivePart.part.chest;
                if(player->coordinates.x >= chest.position.x && player->coordinates.y <= chest.position.y+chest.size.height){
                    *menuState = 1;
                }

                break;

            default:
                SDL_Log("Interactive Type: Unknown\n");
        }
        // Passer à l'élément suivant dans la liste
        interactiveList = (InteractiveList *) interactiveList->next;
    }
}