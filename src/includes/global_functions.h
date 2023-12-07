// global_function.h
#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H

void Log(char * string);
void destroySDL(SDL_Window *, SDL_Renderer *, SDL_Texture *);
void createTextRectButton(SDL_Rect*, SDL_Window*, SDL_Renderer *, SDL_DisplayMode, int rectColorRed, int rectColorGreen, int rectColorBlue, int rectTransparency, char*, char*, SDL_Color);
void inputString(char *string, int length);
long getSize(char *fileName);

#endif
