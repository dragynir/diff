#include"api.h"

int height(struct var* node){
       return node ? node->height : 0;
}

int bfactor(struct var* node){
	return height(node->right) - height(node->left);
}

void fix_height(struct var* node){
	int left_height = height(node->left);
	int right_height = height(node->right);
	node->height = (right_height >  left_height ? right_height:left_height) + 1; 
}

struct var* rotate_left(struct var* q){ 
	struct var* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

struct var* rotate_right(struct var* p){
	struct var* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

struct var* balance(struct var* node){

      fix_height(node);

      if(bfactor(node) == 2){
	      	if(bfactor(node->right) < 0){
	               node->right = rotate_right(node->right);
	      	}
	      	return rotate_left(node);
      }  

      if(bfactor(node) == -2){
	      	if(bfactor(node->left) > 0 ){
	      		node->left = rotate_left(node->left);
	      	}
	      	return rotate_right(node);
      }

      return node;
}

struct var* add_to_tree(struct var* root , struct var*  new_node){

	if(!root) return new_node;
	
	if(strcmp(root->name , new_node->name)  >  0){
         root->right = add_to_tree(root->right , new_node);
	}else{
		root->left = add_to_tree(root->left , new_node);
	}
	return balance(root);// balance fixed !!!!!!!!!!!!!!!!!!!!
}

struct var* find_element_in_tree(struct var* root , struct var* find){

	if(!root)  return 0;	

	struct var* move = root;

	while(move){
		int cmp  = strcmp(move->name , find->name);
		if(cmp == 0){
	         return move;
		}else if(cmp  >  0){
			move = move->right;
		}else{
			move = move->left;
		}
	}
	return 0;
}

void delete_tree(struct var* root){
	if(!root) return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root->name);
	free(root);
}


