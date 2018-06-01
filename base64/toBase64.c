#include"api.h"

char* toBase64(char* inputLine , char* base64Alphabet){


	FILE* input = fopen(inputLine , "r");
	FILE* output = fopen("output.txt" , "w");//установка файла вывода
	int (*returnNextSimbol)(FILE* , char*) = 0;
	output = stdout;

	if(input){
		returnNextSimbol = &returnNextSimbolFromFile;
		inputLine = 0;
	}else{
		returnNextSimbol = &returnNextSimbolFromLine;
	}
	
	unsigned char currentByte = 0 ,  bitPointer6 = 1 , bitPointer8 = 1;
	char outByte6 = 0;
	int tercetCount = 0 , bitCounter8 = 0 , bitCounter6 = 0 ,  byteCounter = 0;

	bitPointer8<<=(7);
	int cmd = 0;

	while((cmd = returnNextSimbol(input , inputLine)) != -1 ? currentByte = cmd: 0){


		byteCounter = (byteCounter + 1) ;

		while(bitCounter8 != 8){

			if(bitPointer8 & currentByte){
				outByte6 = outByte6 | bitPointer6;
			}
			bitCounter6++;
			bitCounter8++;
			if(bitCounter6 == 6){
				showLineSimbol(base64Alphabet[outByte6] , output);
				bitCounter6 = 0;
				outByte6 = 0;
			}
			bitPointer8>>=(1);
			outByte6<<=(1);
		}

		bitCounter8 = 0;
		bitPointer8 = 1;
		bitPointer8<<=(7);

	}
	byteCounter = 3 - byteCounter % 3;

	if(byteCounter){

		if(bitCounter6 != 6){
			while(bitCounter6 != 5){
				outByte6<<=(1);
				bitCounter6++;
			}
			showLineSimbol(base64Alphabet[outByte6] , output);
		}

		fprintf(output , "=");
		if(byteCounter == 2){
			fprintf(output , "=");
		}
	}



}