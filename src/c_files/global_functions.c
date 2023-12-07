// global_function.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../includes/global_functions.h"

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

    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// ----------------------------------------------------------- //

void createTextRectButton(SDL_Rect* rect, SDL_Window* window, SDL_Renderer * renderer, SDL_DisplayMode dm, int rectColorRed, int rectColorGreen, int rectColorBlue, int rectTransparency, char* string,  char* fontPath, SDL_Color fColor){

    //Log("createTextRectButton");

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
    TTF_Font* font = TTF_OpenFont("../src/fonts/arial.ttf", 25);
    // TTF_Font* font = TTF_OpenFont(fontPath, 25);
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

    //Log("createTextRectButton finished !");
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
