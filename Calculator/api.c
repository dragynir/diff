#include"api.h"

struct Lexem* push(struct Lexem* root, struct Lexem* new_lex) {
	new_lex->next = root;
	return new_lex;
}
 
struct Lexem* pop(struct Lexem* root) {
	struct Lexem* keep = root->next;
	root->next = NULL;
	return keep;
}

void delete_stack(struct Lexem* head) {
	struct Lexem* keep;
	while (head) {
		keep = head->next;
		free(head);
		head = keep;
	}
}

void reverse(struct Lexem **Head) {
	struct Lexem* p = NULL, *q = *Head, *n;
	while (q) {
		n = q->next;
		q->next = p;
		p = q;
		q = n;
	}
	*Head = p;
}

char* read_line(FILE *input_file , char *line){
	char lexem;
	int multifactor = 2 , last_size = MAX_LINE_LENGTH;
	int current_s = -1;
    while (fscanf(input_file , "%c", &lexem)) {
    	if(feof(input_file)){
    		free(line);
    		return 0;
    	}

    	if(current_s + 2 >= last_size){

    		line = (char*)realloc((void*)line , current_s * 2);
    		last_size = current_s * 2;
    		multifactor++;
    	}

    	if(lexem == '~'){
    			free(line);
    		return 0;
    	}
    	/*if(lexem == '!'){//очистка консоли ! только перед выражением
    		free(line);
    		line = (char*)malloc(MAX_LINE_LENGTH);
    		current_s = -1;   		
    		system("clear");
    		continue;
    	}*/

		if (lexem == '\n'){
              break;
		} 
		current_s++;
		line[current_s] = lexem;
	}
	current_s++;
	line[current_s] = '\0';
	return line;
}

void show_answer(struct Lexem* lex){
   printf("%d\n" , lex->number);
}
