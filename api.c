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

void read_line(FILE *input_file , char *line){
	memset(line , 0 , MAX_LINE_LENGTH);
	char lexem;
	int current_s = -1;
    while (fscanf(input_file , "%c", &lexem) != -1) {
		if (lexem == '\n'){
              break;
		} 
		line[++current_s] = lexem;
	}
	line[++current_s] = '\0';
}

void show_answer(struct Lexem* lex){
   printf("%d\n" , lex->number);
}
