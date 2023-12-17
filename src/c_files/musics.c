//
// Created by M78st on 17/12/2023.
//

#include <SDL.h>
#include <SDL_mixer.h>

#include "../includes/global_functions.h"

// Structures
#include "../includes/audioData.h"


int DoubleAudioThread(void *data) {
    Log("Begin doubleAudioThread");

    DoubleAudioData *audioData = (DoubleAudioData *)data;

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
    if (*(audioData->menuState) == 0){
        Mix_PlayMusic(music1, audioData->repeat1);
    }
    else{
        Log("Wrong menu State");
    }

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

void executeMusic(SDL_Thread *audio, int menuState){

    SDL_Delay(100);
    if (!Mix_PlayingMusic()) {
        if (menuState == 0) {
            DoubleAudioData *menuMusic = malloc(sizeof(DoubleAudioData));
            menuMusic->string = "./musics/regrets.mp3";
            menuMusic->repeat = 1;
            menuMusic->string1 = "./musics/regrets_avec_rythmique.mp3";
            menuMusic->repeat1 = 5;
            menuMusic->menuState = &menuState;

            SDL_DetachThread(audio);
            audio = SDL_CreateThread(DoubleAudioThread, "AudioThread", menuMusic);
            //SDL_Delay(1000);
        } else if (menuState == 1) {
            AudioData *playMenuMusic = malloc(sizeof(AudioData));
            playMenuMusic->string = "./musics/chillax_un_max.mp3";
            playMenuMusic->repeat = 1;

            SDL_DetachThread(audio);
            audio = SDL_CreateThread(AudioThread, "AudioThread", playMenuMusic);
            //SDL_Delay(1000);
        }
    }
    SDL_Delay(1000);
}