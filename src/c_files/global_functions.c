// global_function.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL.h>

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


    SDL_Log("%s", string);

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
