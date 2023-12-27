//
// Created by M78st on 17/12/2023.
//

#ifndef AUDIODATA_H
#define AUDIODATA_H

typedef struct {
    char *string;
    int repeat;
} AudioData;

typedef struct {
    char *string;
    int repeat;
    char* string1;
    int repeat1;
    int * menuState;
    int musicNumber
} DoubleAudioData;

#endif //AUDIODATA_H
