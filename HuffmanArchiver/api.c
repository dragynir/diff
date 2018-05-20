#include"api.h"

int fill_count_arry(int *count_array , FILE *file , int *message_size) {
	int i = -1, count = 0;
	unsigned char simbol = 0;
	while(1){
		simbol = getc(file);
		(*message_size)++;
		if(feof(file)) break;
		if(count_array[simbol] == 0){
			count++;
		}
		count_array[simbol]++;
	}
	fclose(file);
	return count;
}

void  get_simbol_list(int *count_array , struct tree_knot** list) {
	for (int i = 0 , k = 0; i < ASCII; i++){
		if (count_array[i] != 0) {
			list[k] = (struct tree_knot*)malloc(sizeof(struct tree_knot));
			list[k]->alpha = i;
			list[k]->number = count_array[i];
			list[k]->left = NULL;
			list[k]->right = NULL;
			k++;
		}
	}
}

void quick_sort(struct tree_knot** tree_list , int left, int right) {
	int i = left;
	int j = right;
	struct tree_knot* k;
	int middle = tree_list[(left + right) / 2]->number;
	do {
		while (tree_list[i]->number < middle && i < right) i++;
		while (tree_list[j]->number > middle && j > left) j--;
		if (i <= j) {
			k = tree_list[j];
			tree_list[j] = tree_list[i];
			tree_list[i] = k;
			i++;
			j--;
		}
	} while (i <= j);
	if (i < right) quick_sort(tree_list, i, right);
	if (j > left)  quick_sort(tree_list ,  left, j);
}