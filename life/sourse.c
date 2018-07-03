#include"api.h"
#include"initField.h"
#include"gameLoop.h"
#include"gameRules.h"
#include <unistd.h>
int main(){

	//costume configuration
	int fieldSize = 0 , filledCellsCount = 0;

	printf("Enter field size: ");
	scanf("%d" , &fieldSize);

	char** sceneField = initField(fieldSize);

	printf("Enter count of filled cells:");
	scanf("%d" , &filledCellsCount);

	int cell_x = 0 , cell_y = 0;

	for(int i = 0; i < filledCellsCount; ++i){
		printf("Enter x and y coordinates: ");
		scanf("%d%d" , &cell_x , &cell_y);
		int error = setDefaultFilledCells(sceneField , cell_x , cell_y , fieldSize);
		if(error) --i;
	}
	int count = 100;
	while(count--){
		DrawGameScene(sceneField , fieldSize);
		setNextFilledCells(sceneField , fieldSize);
		sleep (1);
		system("clear");
	}
	

	



	return 0;
}

