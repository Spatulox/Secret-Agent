// Created by Marc

// global_function.h
#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H
#include "./interactivesStruct.h"

void Log(char * string);
void destroySDL(SDL_Window *, SDL_Renderer *, SDL_Texture *);
void inputString(char *string, int length);
long getSize(char *fileName);
int getLastFloorGround(const int * window_height, const int * difficulty);
void freeChainList(InteractiveList** head);
//int addElementToChainList(InteractivePart newPart, InteractiveList** head);
int addElementToChainList(InteractivePart* newPart, InteractiveList** head);
void printInteractiveList(InteractiveList *list);
void displayInteractivePart(InteractivePart *part);

#endif
