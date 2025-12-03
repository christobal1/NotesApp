#ifndef KIRALGORITHM_H
#define KIRALGORITHM_H


extern void initRandom();
extern int randomGenerator(int MAX);
extern char* makeMutable(const char* src);
extern char* kirEncrypt(char text[]);
char* kirDecrypt(char text[]);



#endif
