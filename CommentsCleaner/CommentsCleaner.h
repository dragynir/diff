#include<fstream>


enum Cleaner_State {
	inString , two_LineComment , one_LineComment ,
	endLine , defaultState
};

char getToken(std::ifstream& inputDevice);

void printToken(std::ofstream& outputDevice , const char token);

void findCommentsInLine(std::ifstream& inputDevice , std::ofstream& outputDevice);





