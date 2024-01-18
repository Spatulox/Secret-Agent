//
// Created by Marc on 18/01/2024.
//
#include <SDL.h>
#include "../includes/interactivesStruct.h"
#include "../includes/global_functions.h"

int createInteractive(const int * difficulty, SDL_Renderer * renderer, InteractiveList * interactiveList){


    /*
    switch (*difficulty) {
        case 1:
            Log("1");
        case 2:
            Log("2");
        case 3:
            Log("3");
    }
    */
    // Stairs part
    for (int i = 0; i < ((*difficulty)*3)-1; ++i) {
        InteractivePart * partUpStairs = malloc(sizeof(InteractivePart));

        if(partUpStairs == NULL){
            Log("Impossible to reserve the data");
            freeChainList(interactiveList);
            interactiveList = NULL;
            return 1;
        }

        InteractivePart * partDownStairs = malloc(sizeof(InteractivePart));

        if(partDownStairs == NULL){
            Log("Impossible to reserve the data");
            freeChainList(interactiveList);
            interactiveList = NULL;
            return 1;
        }

        // Create the upstairs
        partUpStairs->type = STAIRS;
        partUpStairs->part.stairs.upDownStairs = 1;
        partUpStairs->part.stairs.linkStairs = 0;

        // Create the downstairs
        partDownStairs->type = STAIRS;
        partDownStairs->part.stairs.upDownStairs = 0;
        partDownStairs->part.stairs.linkStairs = 0;

        // Link the two stairs
        partUpStairs->part.stairs.linkStairs = (struct Stairs *) &partDownStairs->part.stairs;
        partDownStairs->part.stairs.linkStairs = (struct Stairs *) &partUpStairs->part.stairs;


        // Retrieve infos from the pointer inside the struct of the first stairs
        //Stairs * tmp = (Stairs *) partDownStairs->part.stairs.linkStairs;
        //SDL_Log("part up stairs struct %d", tmp->upDownStairs);
        //SDL_Log("part down stairs %p", &partDownStairs);
        //SDL_Log("part down stairs struct%p", &partDownStairs->part.stairs);

        //SDL_Log("%d", *partUpStairs->part.stairs.linkStairs);


        addElementToChainList(partUpStairs, &interactiveList);
        addElementToChainList(partDownStairs, &interactiveList);

    }
    printInteractiveList(interactiveList);

    return 0;
}

void drawInteractiveParts(){

}


// ------------------------------------------------ //

void drawButtons(){

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
