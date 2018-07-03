#include"api.h"


char** initField(int fieldSize){

		char** sceneField = (char**)malloc(sizeof(char*) * fieldSize);

		for(int i = 0; i < fieldSize; ++i){
			sceneField[i] = (char*)malloc(sizeof(char) * fieldSize);
			memset(sceneField[i] , SPACE_NUMBER , sizeof(char) * fieldSize);	
		}

		return sceneField;
}


int setDefaultFilledCells(char** sceneField , int cell_x , int cell_y , int fieldSize){
	if(cell_x >= 0 && cell_x < fieldSize && cell_y < fieldSize && cell_y >= 0){
		sceneField[cell_y][cell_x] = CELL_IMAGE_NUMBER;
		return 0;
	}
	else printf("Wrong coordinates!\nField Size: %d * %d \n" , fieldSize , fieldSize);
	return 1;
}


