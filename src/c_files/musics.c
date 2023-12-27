//
// Created by M78st on 17/12/2023.
//

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "../includes/global_functions.h"

// Structures
#include "../includes/audioData.h"


int DoubleAudioThread(void *data) {
    Log("Begin doubleAudioThread");

    DoubleAudioData *audioData = (DoubleAudioData *)data;

    //SDL_Log("%p", audioData->menuState);
    //SDL_Log("%d", *(audioData->menuState));

    if (audioData == NULL){
        Log("Data are null");
        return 1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        Log("Impossible to initialize the audio part");
        return 1;
    }

    // Load Music
    Mix_Music *music = Mix_LoadMUS(audioData->string);
    if (music == NULL) {
        Log("Impossible to load the music");
        return 1;
    }

    Mix_Music *music1 = Mix_LoadMUS(audioData->string1);
    if (music == NULL) {
        Log("Impossible to load the 2nd music");
        return 1;
    }

    // Start music
    Mix_PlayMusic(music, audioData->repeat);

    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Instant play the other music
    //SDL_Log("%p", audioData->menuState);
    //SDL_Log("%d", *(audioData->menuState));
    if (*(audioData->menuState) == audioData->musicNumber){
        Mix_PlayMusic(music1, audioData->repeat1);
    }
    else{
        Log("Wrong menu State");
        return 0;
    }

    SDL_Log("%d", *(audioData->menuState));

    // Free first music
    if (music != NULL){
        Mix_FreeMusic(music);
    }
    else{
        Log("Impossible to free music   ");
    }

    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Free 2nd music
    if (music1 != NULL){
        Mix_FreeMusic(music1);
    }
    else{
        Log("Impossible to free music1");
    }

    if (audioData != NULL){
        free(audioData);
    }
    else{
        Log("Impossible to free audioData");
    }

    Mix_CloseAudio();
    Mix_Quit();


    return 0;
}


// ----------------------------------------------------------- //

int AudioThread(void *data) {
    Log("Begin AudioThread");

    AudioData *audioData = (AudioData *)data;

    if (audioData == NULL){
        Log("Data are null");
        return 1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        Log("Impossible to initialize the audio part");
        return 1;
    }

    // Load Music
    Mix_Music *music = Mix_LoadMUS(audioData->string);
    if (music == NULL) {
        Log("Impossible to load the music");
        return 1;
    }

    // Start music
    Mix_PlayMusic(music, audioData->repeat);

    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Free first music
    if (music != NULL){
        Mix_FreeMusic(music);
    }
    else{
        Log("Impossible to free music   ");
    }

    if (audioData != NULL){
        free(audioData);
    }
    else{
        Log("Impossible to free audioData");
    }

    Mix_CloseAudio();
    Mix_Quit();

    return 0;
}

// ----------------------------------------------------------- //

void executeMusic(SDL_Thread *audio, int *menuState){

    //SDL_Log("execute music : %p", menuState);
    SDL_Log("execute music : %d", *menuState);
    SDL_Delay(100);
    if (!Mix_PlayingMusic()) {
        if (*menuState == 0) {
            DoubleAudioData *menuMusic = malloc(sizeof(DoubleAudioData));
            menuMusic->string = "./musics/regrets.mp3";
            menuMusic->repeat = 1;
            menuMusic->string1 = "./musics/regrets_avec_rythmique.mp3";
            menuMusic->repeat1 = 5;
            menuMusic->menuState = menuState;
            menuMusic->musicNumber = 0;

            SDL_DetachThread(audio);
            audio = SDL_CreateThread(DoubleAudioThread, "AudioThread", menuMusic);
            //SDL_Delay(1000);
        } else if (*menuState == 1) {
            AudioData *playMenuMusic = malloc(sizeof(AudioData));
            playMenuMusic->string = "./musics/chillax_un_max.mp3";
            playMenuMusic->repeat = 5;

            SDL_DetachThread(audio);
            audio = SDL_CreateThread(AudioThread, "AudioThread", playMenuMusic);
            //SDL_Delay(1000);
        } else if (*menuState == 2) {
            DoubleAudioData *menuMusic = malloc(sizeof(DoubleAudioData));
            menuMusic->string = "./musics/broken.mp3";
            menuMusic->repeat = 1;
            menuMusic->string1 = "./musics/broken_avec_rythmique.mp3";
            menuMusic->repeat1 = 5;
            menuMusic->menuState = menuState;
            menuMusic->musicNumber = 2;

            SDL_DetachThread(audio);
            audio = SDL_CreateThread(DoubleAudioThread, "AudioThread", menuMusic);
            //SDL_Delay(1000);
        }
    }
    // Need to wait but idk why, probably thread interferance or whatever
    SDL_Delay(400);
}