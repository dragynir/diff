#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define VAR_LENGTH 10
#define MAX_LINE_LENGTH 100

struct Lexem {
	char simbol;
	int prior;
	struct Lexem *next;
	int number;
};

struct var {
	char *name;
	int value;
	struct var* left;
	struct var* right;
	int height;
	int assign;
};

struct var* add_to_tree(struct var* root , struct var*  new_node);

struct var* find_element_in_tree(struct var* root , struct var* find);

void delete_tree(struct var* root);

void show_answer(struct Lexem* lex);

void read_line(FILE* input_file  ,char *line);

void reverse(struct Lexem **Head);

void delete_stack(struct Lexem* head);

struct Lexem* pop(struct Lexem* root);

struct Lexem* push(struct Lexem* root, struct Lexem* new_lex);
