#include"api.h"
#include"tree_api.h"

void  send_message(unsigned char **simbol_list , FILE *input , FILE* output , int size){
      int count = 1  , i = 0;
    	unsigned char  out_simbol = 0 ,  bit_pointer = 1 , simbol;
      bit_pointer<<=(7);
      
      while(1) {

          simbol = getc(input);
    		  if(feof(input)) break;

    		  unsigned char* code = simbol_list[simbol];
    	    i = 0;	

    	    while(code[i]){

      	    	  if(code[i] == '1'){
                    out_simbol = out_simbol | bit_pointer;
      	    	  }
      	    	  bit_pointer >>= (1);

      	    	  if(count == 8){
          	    		count = 0;		
          	    		fprintf(output , "%c" , out_simbol);
          	    		bit_pointer = 1;
          	    		bit_pointer<<=(7);
          	    		out_simbol = 0;
      	    	  }

      	    	  i++;
                count++;
    	    }
     
      }

      unsigned char right_bit = count; 
      if(count) fprintf(output , "%c", out_simbol );
      fprintf(output , "%c" ,  right_bit);

}



int main(int argc , char** argv) {



    char *INP_FILE = argv[1];
    char *OUT_FILE = argv[2];
    FILE* input = fopen(INP_FILE , "rb");
    FILE* output = fopen( OUT_FILE, "wb");

    if(!input || !output){
      printf("Read error...\n");
      return 0;
    }

    int *alpha_count_array = (int*)malloc(ASCII * sizeof(int));
    memset(alpha_count_array , 0 , ASCII);
    

    //подсчитываем кол-во встречаемости символов
    int message_size = 0;
    int tree_list_size = fill_count_arry(alpha_count_array , input , &message_size);//file close , count alpha frequency 
    if(!tree_list_size){
      printf("File is empty!!!\n");
      return 0;
    } 
    struct tree_knot** tree_list = (struct tree_knot**)malloc(sizeof(struct tree_knot*) * tree_list_size);
    get_simbol_list(alpha_count_array , tree_list);

    free(alpha_count_array);

    struct tree_knot** keep_list = (struct tree_knot**)malloc(sizeof(struct tree_knot*) * tree_list_size);
    for (int i = 0; i < tree_list_size; ++i){
      	keep_list[i] = tree_list[i];//сохраняем указатели 
        keep_list[i]->use = 1;
    }

    struct tree_knot *tree_root  = make_tree(tree_list , tree_list_size);//строим дерево

    free(tree_list);

    unsigned char len[CODE_LENGTH];
    for (int i = 0; i < CODE_LENGTH; ++i){
          len[i] = 0;
    }
     
    //устанавливаем код для каждого символа  и передаем дерево скобочной записью
    unsigned int bit_count = 0;
    unsigned char treestruct = 0 ,  pointer = 1;
    pointer<<=(7);

    if(!tree_root->left && !tree_root->right){//разбор случая для одной буквы
        tree_root->code = (char*)malloc(2);
        tree_root->code[0] = '0';
        tree_root->code[1] = 0;
        fprintf(output, "%c", '0' );
    }else{   
        set_code(tree_root , len , 0 , output , &treestruct , &bit_count , &pointer );
    }
    if(bit_count){
        fprintf(output , "%c", treestruct );
    }

    //передаем символы обходом в глубину
    unsigned char simbol_count = (tree_list_size - 1);
    fprintf(output , "%c",  simbol_count);
    dfs(tree_root , output);



    //читаем файл второй раз - кодируем сообщение

    input = fopen( INP_FILE , "rb");

    unsigned char **simbol_list = (unsigned char**)malloc(sizeof(unsigned char*) * ASCII);//массив с кодами для каждого символа(чтобы не идти по дереву)
    for (int i = 0; i < tree_list_size; ++i){
        simbol_list[keep_list[i]->alpha] = keep_list[i]->code;
    }

    //отправляем сообщение
    send_message(simbol_list , input ,  output , message_size);

    free(simbol_list);
    delete_tree(tree_root);
    free(keep_list);
    fclose(input);
    fclose(output);


    return 0;
}