#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define ERROR 0
#define TO_BASE_64 1
#define FROM_BASE_64 2

int selectOptionFromUser(int numOfLine , char** usrLine);

int returnNextSimbolFromFile(FILE* input , char* inputLine);

int returnNextSimbolFromLine(FILE* input , char* inputLine);

void showLineSimbol(char simbol , FILE* output);
