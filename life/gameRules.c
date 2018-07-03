#include"api.h"



int countNeighbors(char** sceneField , int y , int x , int fieldSize){

	int neighborsCount = 0;

	if(x > 0){

		if(sceneField[x - 1][y] == CELL_IMAGE_NUMBER || sceneField[x - 1][y] == CELL_WAIT_IMAGE_NUMBER_D)
			neighborsCount++;	

		if(y > 0){
			if(sceneField[x - 1][y - 1] == CELL_IMAGE_NUMBER || sceneField[x - 1][y - 1] == CELL_WAIT_IMAGE_NUMBER_D)
				neighborsCount++;
		}
		if(y < fieldSize - 1){
			if(sceneField[x - 1][y + 1] == CELL_IMAGE_NUMBER || sceneField[x - 1][y + 1] == CELL_WAIT_IMAGE_NUMBER_D)
				neighborsCount++;
		}
	}

	if(x < fieldSize - 1){
		if(sceneField[x + 1][y] == CELL_IMAGE_NUMBER || sceneField[x + 1][y] == CELL_WAIT_IMAGE_NUMBER_D)
			neighborsCount++;

		if(y > 0){
			if(sceneField[x][y - 1] == CELL_IMAGE_NUMBER || sceneField[x][y - 1] == CELL_WAIT_IMAGE_NUMBER_D)
				neighborsCount++;
		}

		if(y < fieldSize - 1){
			if(sceneField[x][y + 1] == CELL_IMAGE_NUMBER || sceneField[x][y + 1] == CELL_WAIT_IMAGE_NUMBER_D)
				neighborsCount++;
		}
	}

	if(y > 0){
		if(sceneField[x][y - 1] == CELL_IMAGE_NUMBER || sceneField[x][y - 1] == CELL_WAIT_IMAGE_NUMBER_D)
			neighborsCount++;
	}

	if(y < fieldSize - 1){
		if(sceneField[x][y + 1] == CELL_IMAGE_NUMBER || sceneField[x][y + 1] == CELL_WAIT_IMAGE_NUMBER_D)
			neighborsCount++;
	}
	
	return neighborsCount;

}



int checkLifeRules(int neighborsCount , int isAlife){
	if(isAlife){

		if(!(neighborsCount == STAY_ALIFE1 || neighborsCount == STAY_ALIFE2)){
			return 1;
		}else{
			return 2;
		}

	}else{
		if(neighborsCount == NEW_LIFE){
			return 3;
		}
	}
	return 0;
}


void setNextFilledCells(char** sceneField , int  fieldSize){

	int neighborsCount = 0;


	for(int y = 0; y < fieldSize; ++y){
		for(int x = 0; x < fieldSize; ++x){

			neighborsCount = countNeighbors(sceneField , x , y , fieldSize);

			int isAlife = checkLifeRules(neighborsCount , sceneField[y][x] == CELL_IMAGE_NUMBER);

			switch(isAlife)
			{
				case 1: sceneField[y][x] = CELL_WAIT_IMAGE_NUMBER_D; break;
				case 2: sceneField[y][x] = CELL_IMAGE_NUMBER; break;
				case 3: sceneField[y][x] = CELL_WAIT_IMAGE_NUMBER_L; break;
			}

		}
	}

}