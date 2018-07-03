#include"qsort.h"


void qsort(void* data , CMP_DATA cmp , const int elementSize , const int left , const int right){

	int i = left;
	int j = right;
	char* d = static_cast<char*>(data);
	char* middle = d + ((i + j) / 2) * elementSize;
	

	do{
		char* di = d + i * elementSize;
		char* dj = d + j * elementSize;
		while(cmp(di , middle) == 1 && i < right){
			i++;
			di = d + i * elementSize;
		}
		while(cmp(dj , middle) == -1 && j > left){
			j--;
			dj = d + j * elementSize;
		}

		if(i <= j){
			for(int d_size = 0; d_size < elementSize; ++d_size){
				char temp = di[d_size];
				di[d_size] = dj[d_size];
				dj[d_size] = temp;
			}
			i++;
			j--;
		}

	}while(i <= j);
	if(i < right) qsort(data , cmp , elementSize , i , right);
	if(j > left) qsort(data , cmp , elementSize , left , j);

}