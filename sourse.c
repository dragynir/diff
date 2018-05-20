#include"api.h"
#include"calculate.h"

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);//добавить чтение из файла
	FILE* input_file = NULL;
	struct Lexem* postfix_line = NULL;
	struct var* variable_tree_root = NULL;
	char line[MAX_LINE_LENGTH] = {0} , cmd;
	int time = 4;
	int equality_count = 0 , i = 0;
	int current_s = -1;
   /* printf("Enter type read type (f , c):");
    scanf("%c" , &cmd);
    if(cmd == 'f'){
    	input_file = fopen("input.txt" , "r");
    	fscanf(input_file , "%d" , &time);
    	fscanf(input_file , "%c" , &cmd);
    	fscanf(input_file , "%c" , &cmd);
    }else{
    	input_file = stdin;
        printf("Enter the number of uses:");
        scanf("%d" , &time);
    }*/
    input_file = stdin;
	while (time--) {

		read_line(input_file , line);
		/*while(line[i]){
            if(line[i++] == '=') equality_count++;
		}*/

		/*if(equality_count > 1){
			printf("Syntactical error!!!\n");equality_count = 0; continue;//продолжить , если > 1 присваивания 
		}*/

		postfix_line = make_postfixf(&variable_tree_root , line , &current_s);//список в обратной польской записи

		if(postfix_line){
             struct Lexem* lex  = calculate_expression(postfix_line);//вычисление выражения
             if(lex)
	         show_answer(lex);
	     	 free(lex);
		}


	    equality_count = 0;
	    current_s = -1;//позиция каретки в строке (для переменных)

	}
	delete_tree(variable_tree_root);
	return 0;
}