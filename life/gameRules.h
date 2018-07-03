int countNeighbors(char** sceneField , int cell_x , int cell_y , int fieldSize);
int checkLifeRules(int neighborsCount , int isAlife);
void setNextFilledCells(char** sceneField , int  fieldSize);