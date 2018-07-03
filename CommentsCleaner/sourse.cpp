#include<fstream>
#include<iostream>
#include"CommentsCleaner.h"



int main(int argv , char** argc){

	std::ifstream fin("src/input.txt");
	std::ofstream fout("src/output.txt");
	

	findCommentsInLine(fin , fout);

	return 0;
}