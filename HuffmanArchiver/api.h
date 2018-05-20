#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define ASCII 256
#define CODE_LENGTH 256

union INT{
	int number;
	unsigned char a[5];
};

struct tree_knot {
	unsigned char alpha;
	struct tree_knot* left;
	struct tree_knot* right;
	unsigned char *code;
	int number;
	char use;
};

int fill_count_arry(int *count_array , FILE* file , int *message_size);
void  get_simbol_list(int *count_array , struct tree_knot** list) ;
void quick_sort(struct tree_knot** tree_list , int left, int right);