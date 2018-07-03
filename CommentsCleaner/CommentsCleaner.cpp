#include"CommentsCleaner.h"
#include<iostream>

char getToken(std::ifstream& inputDevice){
	char token;
	inputDevice.get(token);
	if(inputDevice.eof()) return -1;
	return token;
}

void printToken(std::ofstream& outputDevice , const char token){
	if(token != -1)
	outputDevice << token;
}


void findCommentsInLine(std::ifstream& inputDevice , std::ofstream& outputDevice){
	int totalCommentsSimbol = 0;

	Cleaner_State curr_state = defaultState;
	bool isStar = false , isSlash = false , isBackSlash = false;
	char token = 0 , prev_token = 0;
	while(!inputDevice.eof()){
		token = getToken(inputDevice);
		if(token == '*'){
			isStar = true;
		}else if(token == '/'){
			isSlash = true;
		}

		switch(curr_state){
			case inString:
				if(token == '\"' && prev_token != '\\'){
					curr_state = defaultState;
				}
				printToken(outputDevice , token);
				break;

			case defaultState:
				if(token == '\"'){
					printToken(outputDevice , token);
					curr_state = inString;
					break;
				}
				if(isSlash){
					char simbol = inputDevice.peek();
					if( simbol == '*'){
						curr_state = two_LineComment;
						isSlash = false;
						getToken(inputDevice);
						break;
					}else if(simbol == '/'){
						curr_state = one_LineComment;
						isSlash = false;
						getToken(inputDevice);
						break;
					}	
				}
				printToken(outputDevice , token);
			 	break;

			case two_LineComment:

				if(isStar && !isSlash && inputDevice.peek() == '/'){
					
						curr_state = defaultState;
						isStar = false;
						printToken(outputDevice , ' ');
						getToken(inputDevice);
						totalCommentsSimbol++;		
				}
				printToken(outputDevice , ' ');
				break;

			case one_LineComment:
				if(token == '\n'){
					printToken(outputDevice , '\n');
					isSlash = false;
					isStar = false;
					curr_state = defaultState;
					break;
				}else{
					totalCommentsSimbol++;
				}
				printToken(outputDevice , ' ');
				break;
		}


		prev_token = token;
		isSlash = false;
		isStar = false;

	}




}
