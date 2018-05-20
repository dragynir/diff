#pragma once

struct var* set_variable(struct var** variable_list , char* name , int *current_s); 

struct Lexem* remove_operator(struct Lexem* operators_stack, struct Lexem*  new_lexem, struct Lexem** out_stack);

struct Lexem* make_postfixf(struct var** variable_tree_root , char *line ,int *current_s);

struct Lexem* calculate_expression(struct Lexem* root);

int calculate(struct Lexem* first_operand);
