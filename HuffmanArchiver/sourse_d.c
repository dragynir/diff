#include <stdlib.h>
#include <stdio.h>
#include"api.h"
#include"tree_api.h"

void decode_message(FILE *input , FILE *output , struct tree_knot* root  , int fall_bit){
    struct tree_knot* move_knot = root;
    int  count = 0  , keep = fall_bit ;
    unsigned char  *buffer[3] ,  pointer = 1 , is_last_byte = 0;
    unsigned char simbol, prev_simbol , mid_simbol;
    pointer<<=(7);

    if(fall_bit == 0){
        fall_bit = 8;
    }
    fall_bit--;
    fscanf(input , "%c" , &prev_simbol);
    fscanf(input , "%c" , &mid_simbol);

    while(1){

        fscanf(input , "%c" , &simbol);

        if(feof(input)){
            is_last_byte = 1;
        }

        while(count != 8){

              if(is_last_byte && fall_bit == 0){
                break;
              }
            	if(pointer & prev_simbol){
                if(move_knot->right)
            		move_knot = move_knot->right;
            	}else{
                if(move_knot->left)
            		move_knot = move_knot->left;
            	}
              count++;
              pointer>>=(1);
              if(is_last_byte){
                 fall_bit--;
              }
              if(move_knot->use == 1){
                fprintf(output , "%c", move_knot->alpha );              
                move_knot = root;
              }

        }

        if(feof(input)) break;
        pointer = 1;
        pointer<<=(7);
        count = 0;
        prev_simbol = mid_simbol;
        mid_simbol = simbol;

    }     
}


int make_bracketed_line(unsigned char *bracketed_line , int length , struct tree_knot* root , FILE *input ){

 
    struct tree_knot* move_knot = root;
    int  count = 0 , i = 1 , bracket_count = 0 , end = 0;
    unsigned char simbol , pointer = 1 , check_pointer = 1;
    pointer<<=(7);check_pointer<<=(6);

    
    while(1){

        if(feof(input) || end) break;
        simbol = getc(input);

        if(i == 1){
             if(!(pointer & simbol) && !(check_pointer & simbol)){
                 bracketed_line[i++] = '0';
                 break;
             }
        }


        while(count != 8){

            if(move_knot->use == 1){
                bracketed_line[i++] = move_knot->alpha;

                if(move_knot->alpha == '(' || move_knot->alpha == ')'){

                    if(move_knot->alpha == '('){
                       bracket_count++;
                    }else if(move_knot->alpha == ')'){
                       bracket_count--;
                    }
                    if(bracket_count == 0){
                       end = 1;
                       break;
                    }
                    
                }

                move_knot = root;
              
            }

            if(pointer & simbol){
              move_knot = move_knot->right;
            }else{
              move_knot = move_knot->left;
            }
            count++;
            pointer>>=(1);

        }



        pointer = 1;
        pointer<<=(7);
        count = 0;
    }


  return i;
}


struct tree_knot* make_new_tree(unsigned char *bracketed_line  , int *i , unsigned char *alpha_list , int *list_count , int line_length){
   (*i)++;
   struct tree_knot* p;
   p =(struct tree_knot*) malloc(sizeof(struct tree_knot));
   (*i)++;
   if(bracketed_line[(*i)] == '0' || bracketed_line[(*i)] == ')' ){
      p->left = NULL;
      p->right = NULL;
      p->alpha = alpha_list[(*list_count)++];
      p->use = 1;
   }else{
      p->left = make_new_tree(bracketed_line , i , alpha_list , list_count , line_length);
      (*i)--;
      p->right = make_new_tree(bracketed_line , i , alpha_list , list_count , line_length);
      (*i)++;
   }
   return p;
}
                         

int main(int argc , char **argv){

  char *INP_FILE = argv[1];
  char *OUT_FILE = argv[2];
  FILE* input =  fopen(INP_FILE , "rb");
  FILE* output = fopen(OUT_FILE , "wb"); 

  if(!input || !output){
    printf("error\n");
  }

  unsigned char bit_act;
  fscanf(input , "%c" , &bit_act);

  if(feof(input)){
     printf("File is empty!!!");
     return 0;
  }
  
  fseek(input , -1 , SEEK_END);
  fscanf(input , "%c" , &bit_act);
  int fall_bit = bit_act;
  fseek(input , 0 , SEEK_SET);
    
    

   struct tree_knot** decode_tree_list = (struct tree_knot**)malloc(sizeof(struct tree_knot*) * 3);
   for (int i = 0; i < 3; ++i){
        decode_tree_list[i] = (struct tree_knot*)malloc(sizeof(struct tree_knot));
        decode_tree_list[i]->use = 1;
        decode_tree_list[i]->number = 1;
   }
   decode_tree_list[0]->alpha = '0';
   decode_tree_list[0]->number = 2;
   decode_tree_list[1]->alpha = ')';
   decode_tree_list[2]->alpha = '(';


   struct tree_knot* decode_tree_root = make_tree(decode_tree_list , 3);
   free(decode_tree_list);
   //delete tree

   unsigned char bracketed_line[1024];

   int br_line_length = make_bracketed_line(bracketed_line , 1024 , decode_tree_root , input );
   bracketed_line[0] = '(';
   bracketed_line[br_line_length] = ')';
  
   unsigned char alpha_count;
   fscanf(input , "%c" , &alpha_count);
  
   unsigned char *alpha_list = (unsigned char*)malloc(sizeof(unsigned char) * (alpha_count + 1));
    
   for (int i = 0; i < alpha_count + 1; ++i){
     fscanf(input , "%c" , &alpha_list[i]);
   }
                       
   int i = 0 , list_count = 0;
  
   struct tree_knot *root = make_new_tree(bracketed_line  , &i , alpha_list , &list_count , br_line_length);
   
   decode_message(input , output , root , fall_bit);
   delete_tree(decode_tree_root);
   free(alpha_list);

	 return 0;
}