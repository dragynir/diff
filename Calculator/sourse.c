#include"api.h"
#include"calculate.h"

int main() {
	FILE* input_file = NULL;
	struct Lexem* postfix_line = NULL;
	struct var* variable_tree_root = NULL;
	char* line = NULL;
	int equality_count = 0;
	int current_s = -1 ;
    input_file = stdin;
	while (1) {
		line = (char*)malloc(MAX_LINE_LENGTH);
		line = read_line(input_file , line);
		if(!line) break;
		char* k = line;
		postfix_line = make_postfixf(&variable_tree_root , line , &current_s);//список в обратной польской записи

		if(postfix_line){
             struct Lexem* lex  = calculate_expression(postfix_line);//вычисление выражения
             if(lex)
	         	show_answer(lex);
	     	 free(lex);
	   
		}


	    equality_count = 0;
	    current_s = -1;//позиция каретки в строке (для переменных)
	    free(line);

	}

	delete_tree(variable_tree_root);
	return 0;
}