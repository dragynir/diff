#pragma once
struct tree_knot* make_tree(struct tree_knot** tree_list , int tree_list_size);
void delete_tree(struct tree_knot* root);
void set_code(struct tree_knot* root , unsigned char *code , int len , FILE *f , unsigned char *treestruct , unsigned int *bit_count  , unsigned char *pointer);
void dfs(struct tree_knot *root , FILE *f);
