//
// Created by Marc on 13/01/2024.
//

#ifndef STRUCTPLAYER_H
#define STRUCTPLAYER_H

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int height;
    int width;
} Size;

typedef struct {
    Point coordinates;
    Size size;
    char * pathToPngFile;
    int verticalFlip;
} Player;

#endif //STRUCTPLAYER_H
