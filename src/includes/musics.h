//
// Created by Marc on 17/12/2023.
//

#ifndef MUSICS_H
#define MUSICS_H

int DoubleAudioThread(void *data);
int AudioThread(void *data);
void executeMusic(SDL_Thread *audio, int *menuState);

#endif //MUSICS_H
