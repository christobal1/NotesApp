#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kirAlgorithm.h"

//Für irgendwann:
void initRandom(){
    srand(time(NULL));
}

//Für irgendwann:
int randomGenerator(int MAX){
    
    return rand() % MAX;
}

//char[] zu char*
char* makeMutable(const char* src){
    char* buf = malloc(strlen(src) + 1);
    strcpy(buf, src);
    return buf;
}

char* kirEncrypt(char text[]){
    int length = strlen(text);

    int a=2;
    while((length % a) != 0){
        a++;
    }

    int b = length / a;

    for(int i=0; i<length; i++){
        text[i] = text[i] + b;
    }

    return text;
    
}

char* kirDecrypt(char text[]){
    int length = strlen(text);

    int a=2;
    while((length % a) != 0){
        a++;
    }

    int b = length / a;

    for(int i=0; i<length; i++){
        text[i] = text[i] - b;
    }

    return text;
}