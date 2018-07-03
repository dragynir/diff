
#include<fstream>
#include<vector>
#include"qsort.h"
#include<iostream>

void getDataInt(const int elementsCount , std::ifstream& fin , std::vector<int>& data){

	for(int i = 0; i < elementsCount; ++i){
		int d = 0;
		fin >> d;
		data.push_back(d);
	}

}


int cmpDataElements(const void* leftData , const void* rightData){
	const int left = *static_cast<const int*>(leftData);
	const int right = *static_cast<const int*>(rightData);
	if(left < right) return -1;
	else return left > right;	
}


int main(){

	std::ifstream fin("input.txt");

	int elementsCount = 0;
	fin >> elementsCount;


	//std::vector<int> data;

	int arr[elementsCount];
	for(int i =0; i < elementsCount; ++i){
		fin >> arr[i];
	}
	//getDataInt(elementsCount , fin , data);

	/*for(int i = 0; i < elementsCount; i++){
		std::cout<< data[i] <<" ";
	}*/
	for(int i = 0; i < elementsCount; i++){
		std::cout<< arr[i] <<" ";
	}
	std::cout<<std::endl;
	CMP_DATA cmp = &cmpDataElements;
	//void qsort(void* data , CMP_DATA cmp , const int elementSize , const int left , const int right)
	//qsort(&data[0] , cmp , 4 , 0 , elementsCount - 1 );
	qsort(arr, cmp , 4 , 0 , elementsCount - 1 );


	/*for(int i = 0; i < elementsCount; i++){
		std::cout<< data[i] <<" ";
	}*/
	for(int i = 0; i < elementsCount; i++){
		std::cout<< arr[i] <<" ";
	}


	
	return 0;
}