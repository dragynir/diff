#include"api.h"
#include"fromBase64.h"



void fromBase64(char* inputLine , char* base64Alphabet){

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
	char outByte8 = 0 , cmd = 0;
	int tercetCount = 0 , bitCounter8 = 0 , bitCounter6 = 0 ,  byteCounter = 0;
	bitPointer6<<=(5);
	bitPointer8<<=(7);

	while((cmd = returnNextSimbol(input , inputLine)) != -1 ? currentByte = cmd: 0){

		if(isalpha(currentByte)){
			if(islower(currentByte)){
				currentByte = currentByte - 71;
			}else{
				currentByte = currentByte - 65;
			}
		}
		else if(isdigit(currentByte)){
			currentByte = currentByte + 4;
		}else if(currentByte == '+'){
			currentByte = 62;
		}else if(currentByte == '/'){
			currentByte = 63;
		}else if(currentByte == '=') return;

		/*for(int i = 0; i < 64; ++i){
			if(base64Alphabet[i] == currentByte){
				currentByte = i;break;
			}
		}
		if(currentByte == '=') return;*/

		while(bitCounter6 != 6){

			if(bitPointer6 & currentByte){
				outByte8 = outByte8 | bitPointer8;
			}
			bitCounter8++;
			bitCounter6++;
			if(bitCounter8 == 8){
				showLineSimbol( outByte8 , output);
				bitCounter8 = 0;
				bitPointer8 = 1;
				bitPointer8<<=(7);
				outByte8 = 0;
			}
			bitPointer6>>=(1);

			if(bitCounter8 != 0)
				bitPointer8>>=(1);
		}

		bitCounter6 = 0;
		bitPointer6 = 1;
		bitPointer6<<=(5);

	}

}			