#include"api.h"

void DrawGameScene(char** sceneField , int fieldSize){

	int isEmptyField = 1;

	for(int x = 0; x < fieldSize + 2; ++x){
		printf("-");
	}
	printf("\n");

	for(int y  = 0; y < fieldSize; ++y)
	{

		for(int x = 0; x < fieldSize; ++x)
		{
			if(x == 0) 
				printf("|");

			if(sceneField[y][x] == CELL_WAIT_IMAGE_NUMBER_L){
				sceneField[y][x] = CELL_IMAGE_NUMBER;
			}
			if(sceneField[y][x] == CELL_WAIT_IMAGE_NUMBER_D){
				sceneField[y][x] = SPACE_NUMBER;
			}


			printf("%c" , sceneField[y][x]);

			if(x == fieldSize - 1)
				printf("|");
		
		}
		printf("\n");
	}

	for(int x = 0; x < fieldSize + 2; ++x){
		printf("-");
	}
	printf("\n");

}