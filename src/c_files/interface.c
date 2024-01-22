//
// Created by Marc on 06/12/2023.
//


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../includes/interface.h"
#include "../includes/global_functions.h"
#include "../includes/musics.h"

// Structures
#include "../includes/audioData.h"

// ----------------------------------------------------------- //
void createTextRectButton(SDL_Rect* rect, SDL_Window* window, SDL_Renderer * renderer, SDL_DisplayMode dm, int rectColorRed, int rectColorGreen, int rectColorBlue, int rectTransparency, char* string,  char* fontPath, SDL_Color fColor){

    if(rectColorRed > 255){
        rectColorRed = 255;
        Log("Too high value for rectColorRed");
    }
    if (rectColorRed < 0){
        rectColorRed = 0;
        Log("Too low value for rectColorRed");
    }
    if(rectColorGreen > 255){
        rectColorGreen = 255;
        Log("Too high value for rectColorGreen");
    }
    if (rectColorGreen < 0){
        rectColorGreen = 0;
        Log("Too low value for rectColorGreen");
    }
    if(rectColorBlue > 255){
        rectColorBlue = 255;
        Log("Too high value for rectColorBlue");
    }
    if (rectColorBlue < 0){
        rectColorBlue = 0;
        Log("Too low value for rectColorBlue");
    }
    if(rectTransparency > 255){
        rectTransparency = 255;
        Log("Too high value for rectTransparency");
    }
    if (rectTransparency < 0){
        rectTransparency = 0;
        Log("Too low value for rectTransparency");
    }


    SDL_SetRenderDrawColor(renderer, rectColorRed, rectColorGreen, rectColorBlue, rectTransparency); // Remplacez r, g, b et a par les valeurs de couleur souhaitées
    SDL_RenderDrawRect(renderer, rect);
    SDL_RenderFillRect(renderer, rect);

    // Load font
    //TTF_Font* font = TTF_OpenFont("../src/fonts/arial.ttf", 25);
    TTF_Font* font = TTF_OpenFont(fontPath, 25);
    if (font == NULL){
        Log("ERROR : Impossible to import the font");
        TTF_CloseFont(font);
        destroySDL(window, renderer, NULL);
    }



    SDL_Surface* surface = TTF_RenderText_Solid(font, string, fColor);
    if (surface == NULL){
        Log("ERROR : Impossible to create the surface for the texture");
        TTF_CloseFont(font);
        SDL_FreeSurface(surface);
        destroySDL(window, renderer, NULL);
    }
    TTF_CloseFont(font);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL){
        Log("ERROR : Impossible to create the texture");
        TTF_CloseFont(font);
        SDL_FreeSurface(surface);
        destroySDL(window, renderer, texture);
    }

    SDL_FreeSurface(surface);



    if (SDL_QueryTexture(texture, NULL, NULL, &dm.w, &dm.h) != 0){
        Log("ERROR : Impossible load the texte in RAM");
        destroySDL(window, renderer, texture);
    }


    if (SDL_RenderCopy(renderer, texture, NULL, rect) != 0){
        Log("ERROR : Impossible to print the texte");
        destroySDL(window, renderer, texture);
    }

}

// ----------------------------------------------------------- //

void createMenu(SDL_Window * window, SDL_Renderer* renderer, int width, int height, SDL_DisplayMode dm, char* fontPath, Button buttons[], int * menuState){

    SDL_RenderClear(renderer);
    Mix_HaltMusic();

    buttons[0].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 3) - (height / 2), width, height - (dm.h / 30)};
    buttons[0].text = "Jouer";

    buttons[1].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 2) - (height / 2), width, height - (dm.h / 30)};
    buttons[1].text = "Parametres";

    buttons[2].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 1.5) - (height / 2), width, height - (dm.h / 30)};
    buttons[2].text = "Quitter le jeu";

    buttons[3].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 3) - (height / 2), width, height - (dm.h / 30)};
    buttons[3].text = "Facile";

    buttons[4].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 2) - (height / 2), width, height - (dm.h / 30)};
    buttons[4].text = "Normal";

    buttons[5].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 1.5) - (height / 2), width, height - (dm.h / 30)};
    buttons[5].text = "Difficile";

    buttons[6].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 3.5) - (height / 2), width, height - (dm.h / 30)};
    buttons[6].text = "Associations des touches";

    buttons[7].rect = (SDL_Rect){(dm.w / 2) - (width) + width/3, (dm.h / 2.5) - (height / 2), width/2, height - (dm.h / 30)};
    buttons[7].text = "Gauche";

    buttons[8].rect = (SDL_Rect){(dm.w / 2) + (width / 4), (dm.h / 2.5) - (height / 2), width/2, height - (dm.h / 30)};
    buttons[8].text = "Droite";

    buttons[9].rect = (SDL_Rect){(dm.w / 2) + (width / 4) - (width / 2), (dm.h / 1.75) - (height / 2), width/2, height - (dm.h / 30)};
    buttons[9].text = "Interagir";

    buttons[10].rect = (SDL_Rect){(dm.w / 2) - (width / 2), (dm.h / 1.2) - (height / 2), width, height - (dm.h / 30)};
    buttons[10].text = "Retour";

    SDL_Color fColor = {0, 0, 0};


    //SDL_Log("creating buttons menu state : %d", *menuState);
    if (*menuState == 0){
        // Draw buttons on the renderer
        for (int i = 0; i < 3; i++) {
            createTextRectButton(&buttons[i].rect, window, renderer, dm, 255, 255, 255, 255, buttons[i].text, fontPath, fColor);
        }
    }
    else if(*menuState == 1){
        for (int i = 3; i < 6; i++) {
            createTextRectButton(&buttons[i].rect, window, renderer, dm, 255, 255, 255, 255, buttons[i].text, fontPath, fColor);
        }
    }
    else{
        Log("Wrong menu state, can't draw buttons");
    }

    Log("Menu created");

}

// ----------------------------------------------------------- //


// Fonction pour créer les boutons
