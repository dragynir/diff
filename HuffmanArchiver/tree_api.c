#include"api.h"

struct tree_knot* make_tree(struct tree_knot** tree_list , int tree_list_size) {
	struct tree_knot* new_knot = NULL;

	if (tree_list_size == 1) {
		tree_list[0]->left = NULL;
		tree_list[0]->right = NULL;
		return tree_list[0];
	}

	int first = 0 , second = 1 , diff = 0;
	for (; second < tree_list_size;){
		quick_sort(tree_list, diff , tree_list_size - 1);
		new_knot = (struct tree_knot*)malloc(sizeof(struct tree_knot));
		new_knot->number = tree_list[first]->number + tree_list[second]->number;
		new_knot->left = tree_list[first];
		new_knot->right = tree_list[second];
		new_knot->alpha = 0;
		new_knot->use = 0;
		tree_list[first] = NULL;
		tree_list[second] = new_knot;
		diff++;
		second++; first++;
	}
	return new_knot;
}


void changeByte(unsigned char *treestruct  ,unsigned int *bit_count , unsigned char *pointer , FILE *f){
	if((*bit_count) == 8){
		fprintf(f , "%c", (*treestruct) );
		(*treestruct) = 0;
		(*bit_count) = 0;
		(*pointer) = 1;
		(*pointer)<<=(7);
	}
}


void set_code(struct tree_knot* root , unsigned char *code , int len , FILE *f  ,unsigned char *treestruct  ,unsigned int *bit_count , unsigned char *pointer) {
	if (root == NULL) return;
	
	root->code = (unsigned char*)malloc(sizeof(unsigned char) * (len + 1) );
	(*bit_count)++;
	(*pointer)>>=(1);
	//printf("0");
    changeByte(treestruct  , bit_count , pointer , f);

    if(root->left || root->right){
        //printf("(");
   
    	(*treestruct) = (*treestruct) | (*pointer);
    	(*pointer)>>=(1);
    	 
    	(*bit_count)++;
    	changeByte(treestruct  , bit_count , pointer , f);
        (*pointer)>>=(1);
        
        (*bit_count)++;
        changeByte(treestruct  , bit_count , pointer , f);
    }
    
	for (int i = 0; i < len; ++i){
		root->code[i] = code[i];
	}

	root->code[len] = 0;
	code[len] = '0';
	if(root->left){
       	set_code(root->left , code , len + 1 , f , treestruct , bit_count , pointer );
	}
	code[len] = '1';   
	if(root->right){
        set_code(root->right, code , len + 1 , f , treestruct , bit_count , pointer);
	}
	if(root->left || root->right){
	    //printf(")");
		(*treestruct) = (*treestruct) | (*pointer);
		(*pointer)>>=(1);
		 
		
		(*bit_count)++;
	    changeByte(treestruct  , bit_count , pointer , f);
	     
	    (*treestruct) = (*treestruct) | (*pointer);
	    (*pointer)>>=(1);
	   
		(*bit_count)++;
		changeByte(treestruct  , bit_count , pointer , f);
    
    }

}


void dfs(struct tree_knot *root , FILE *f){
	if(!root) return;
	if(!root->left && !root->right){
        fprintf(f , "%c",  root->alpha);
	}
	dfs(root->left  , f);
	dfs(root->right , f);
}




void delete_tree(struct tree_knot* root){
     if(!root) return;
     free(root->code);
     free(root);
     delete_tree(root->left);
     delete_tree(root->right);
}


