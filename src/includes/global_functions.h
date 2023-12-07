// global_function.h
#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H

void Log(char * string);
void destroySDL(SDL_Window *, SDL_Renderer *, SDL_Texture *);
void inputString(char *string, int length);
long getSize(char *fileName);

#endif
