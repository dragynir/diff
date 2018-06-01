#include"api.h"


int selectOptionFromUser(int numOfLine , char** usrLine){

	if(numOfLine != 3) return ERROR;
	
	if(!strcmp(usrLine[1] , "-t")){
		return TO_BASE_64;
	}else if(!strcmp(usrLine[1] , "-f")){
		return FROM_BASE_64;
	}else return ERROR;

}

int returnNextSimbolFromFile(FILE* input , char* inputLine){
	char simbol = 0;
	int error = 0;
	error = fscanf(input , "%c" , &simbol);
	if(error == -1) return error;
	else return simbol;
}

int returnNextSimbolFromLine(FILE* input , char* inputLine){
	static int linePointer = 0;
	if(inputLine[linePointer] != '\0'){
		return inputLine[linePointer++];
	}else{
		return -1;
	}
}

void showLineSimbol(char simbol , FILE* output){
		fprintf(output , "%c" , simbol);
}