// somme.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>

#include "../includes/global_functions.h"

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
}

int somme(int a, int b) {
    return a + b;
}
