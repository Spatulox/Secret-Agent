//
// Created by M78st on 13/01/2024.
//

#include <SDL.h>
#include <SDL_image.h>

#include "../includes/global_functions.h"
#include "../includes/structPlayer.h"

// ----------------------------------------------------------- //

int loadPlayer(SDL_Renderer * renderer, SDL_DisplayMode dm, Player * imgInfos){

    Log("Loading player");
    SDL_Surface* imageSurface = IMG_Load(imgInfos->pathToPngFile);
    if(imageSurface == NULL){
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
    dstRect.x = (dm.w)*0.10;
    dstRect.y = dm.h - imageHeight;
    dstRect.w = imageWidth;
    dstRect.h = imageHeight;

    imgInfos->coordinates.x = (dm.w)*0.10;
    imgInfos->coordinates.y = dm.h - imageHeight;
    imgInfos->size.height = imageHeight;
    imgInfos->size.width = imageWidth;
    imgInfos->verticalFlip = 0;
    SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

}

// ----------------------------------------------------------- //

int rightPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player){

    SDL_Surface* imageSurface = IMG_Load(player->pathToPngFile);
    if(imageSurface == NULL){
        return 1;
    }

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(imageTexture == NULL){
        return 1;
    }

    SDL_Rect dstRect;
    //player->size.width
    if(player->coordinates.x + dm.w/100 + player->size.width < dm.w-((dm.w)*0.10)){
        player->coordinates.x = player->coordinates.x + dm.w/100;
    }
    dstRect.x = player->coordinates.x;
    dstRect.y = player->coordinates.y;
    dstRect.w = player->size.width;
    dstRect.h = player->size.height;

    if(player->verticalFlip == 0){
        SDL_RenderCopyEx(renderer, imageTexture, NULL, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        player->verticalFlip = 1;
    }
    else{
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);
        player->verticalFlip = 0;
    }
    //Log("Right player");
}

// ----------------------------------------------------------- //

int leftPlayer(SDL_Renderer* renderer,  SDL_DisplayMode dm, Player * player){
    SDL_Surface* imageSurface = IMG_Load(player->pathToPngFile);
    if(imageSurface == NULL){
        return 1;
    }

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(imageTexture == NULL){
        return 1;
    }

    SDL_Rect dstRect;
    if(player->coordinates.x - dm.w/100 > (dm.w)*0.10){
        player->coordinates.x = player->coordinates.x - dm.w/100;
    }
    dstRect.x = player->coordinates.x;
    dstRect.y = player->coordinates.y;
    dstRect.w = player->size.width;
    dstRect.h = player->size.height;

    if(player->verticalFlip == 0){
        SDL_RenderCopyEx(renderer, imageTexture, NULL, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        player->verticalFlip = 1;
    }
    else{
        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);
        player->verticalFlip = 0;
    }
    //Log("Left player");
}