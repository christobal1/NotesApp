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

char* kirEncrypt(unsigned char* text, int length){

    int a=2;
    while((length % a) != 0){
        a++;
    }

    int b = length / a;

    for(int i=0; i<length; i++){
        if((i % a) == 0){
            text[i] = text[i] + a;
        } else if ((i % 2) == 0){
            text[i] = text[i] - 3;
        } else if ((i % 3) == 0){
            text[i] = text[i] + 5;
        } else {
            text[i] = text[i] + b;
        }
    }

    return (char*)text;
    
}

char* kirDecrypt(unsigned char* text, int length){

    int a=2;
    while((length % a) != 0){
        a++;
    }

    int b = length / a;

    for(int i=0; i<length; i++){
        if((i % a) == 0){
            text[i] = text[i] - a;
        } else if ((i % 2) == 0){
            text[i] = text[i] + 3;
        } else if ((i % 3) == 0){
            text[i] = text[i] - 5;
        } else {
            text[i] = text[i] - b;
        }
    }

    return (char*)text;
}