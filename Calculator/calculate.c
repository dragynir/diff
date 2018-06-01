#include"api.h"
#include"calculate.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
int calculate(struct Lexem* first_operand) {

	struct Lexem* keep = first_operand->next->next;

	switch (first_operand->next->next->simbol)
	{
	case '+':first_operand->number = first_operand->number + first_operand->next->number; break;
	case '-':first_operand->number = first_operand->number - first_operand->next->number; break;
	case '*':first_operand->number = first_operand->number * first_operand->next->number; break;
	case '/':
		if (first_operand->next->number) {
			first_operand->number = first_operand->number / first_operand->next->number;
		}else {
			printf("Devide by zero!!!\n"); return 0;
		} 
		break;

	case '%':first_operand->number = first_operand->number % first_operand->next->number; break;
	}

	free(first_operand->next);
	first_operand->next = keep->next;
	free(keep);
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////вычисление выражения
struct Lexem* calculate_expression(struct Lexem* root) {

	struct Lexem* first_operand = NULL, *second_operand = root;
	int success = 1;

	while (second_operand != NULL) {
		if (!success) {
			delete_stack(root);//////////
			return 0;
		}  
		if (first_operand && second_operand->next && second_operand->next->simbol) {
			success = calculate(first_operand);
			first_operand = NULL;
			second_operand = root;
		}else {
			first_operand = second_operand;
			second_operand = second_operand->next;
		}

	}
	return root;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
struct var* set_variable(struct var** variable_tree_root , char* line , int *current_s) {

	struct var* new_var = (struct var*)malloc(sizeof(struct var));//создаем новую переменную
	int  move_line = (*current_s);
	char simbol = 0;
	int count = 0;

    while (1) {//рассщитываем размер переменной
		simbol = line[move_line];
		if (simbol != ' ' && simbol != '\n' && simbol != '=' && simbol != 0 && simbol!= ')' && simbol != '+' && simbol != '-' && simbol != '*' && simbol != '/' && simbol != '%' ) {
			//if (count < VAR_LENGTH) {
			     count++;
			//}
		}else break;
		/*if(count >= VAR_LENGTH ){
			free(new_var);
		    printf("Variable size error!!!\n");
			return 0;	
		}*/
		count++;
		move_line++;
	}

	new_var->name = (char*)malloc(count + 1);
	count = 0;

	while (1) {
		simbol = line[(*current_s)];
		if (simbol != ' ' && simbol != '\n' && simbol!= '=' && simbol != 0 && simbol!= ')' && simbol != '+' && simbol != '-' && simbol != '*' && simbol != '/' && simbol != '%' ) {
			new_var->name[count++] = simbol;
			/*if (count < VAR_LENGTH) {
				new_var->name[count++] = simbol;
			}*/
			//else {
				/*free(new_var->name);
				free(new_var);
				printf("Variable size error!!!\n");
				return 0;*/
			//}
		}else{
          if(simbol == '='){
          	(*current_s)--;///////////
          }
          break;
		} 
		(*current_s)++;
	}
	new_var->name[count] = '\0';

	
	struct var* find = find_element_in_tree(*variable_tree_root , new_var);	//ищем переменную в дереве
	simbol = line[++(*current_s)];
    while(simbol == ' '){
        simbol = line[++(*current_s)];
    }

	if(simbol == '='){

        struct Lexem* set_new_var;
         
        if(find) {//если нашли переменную - выполняем присваивание
        	  free(new_var->name);
              free(new_var);
              set_new_var = make_postfixf(variable_tree_root , line , current_s);
              set_new_var  = calculate_expression(set_new_var);
              if(!set_new_var){
      			printf("Error\n");
                     return 0;
              }
              find->value = set_new_var->number;
              free(set_new_var);
              // find->assign = 0;
              find->assign = 1;////////////////Если поставить , то множественное присваивание невозможно
              return find;

        }else{//добавляем новую переменныю и ставим флаг присваивани, чтобы не выводить рез на экран и не продолжать вычисления

             find = new_var;
             find->left = NULL;
             find->right = NULL;
             set_new_var = make_postfixf(variable_tree_root , line , current_s);
             set_new_var  = calculate_expression(set_new_var);

             if(!set_new_var){
             	free(new_var->name);
             	free(new_var);
              	printf("Error\n");
                     return 0;
             }
             find->value = set_new_var->number;
             free(set_new_var);
             *variable_tree_root = add_to_tree(*variable_tree_root , find);
             	if(!(*variable_tree_root)){
                    *variable_tree_root = new_var;
	            }  
	            //find->assign = 0;
             find->assign = 1;////////////////Если поставить , то множественное присваивание невозможно
             return find;
        }

	}else if(find){// не "=" - значит возвращаем переменную
	    find->assign = 0;
	    free(new_var->name);
	    free(new_var);
        return find;
	} else{
          printf("Syntactical error1 or Variable not found !!!\n");
 		  free(new_var->name);
 		  free(new_var);
	}

	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Lexem* remove_operator(struct Lexem* operators_stack, struct Lexem*  new_lexem, struct Lexem** out_stack) {

	struct Lexem* lex_pointer = operators_stack, *keep;

	if (!new_lexem->prior && operators_stack) {//если  закрывающая скобка
		while (lex_pointer->prior != 0) {
			keep = lex_pointer->next;
			operators_stack = pop(lex_pointer);
			*out_stack = push(*out_stack, lex_pointer);
			lex_pointer = keep;
		}

		operators_stack = lex_pointer->next;
		free(lex_pointer);
		free(new_lexem);
		return operators_stack;
	}
	else {
		while (lex_pointer && lex_pointer->prior >= new_lexem->prior && lex_pointer->prior) {
			keep = lex_pointer->next;
			operators_stack = pop(lex_pointer);
			*out_stack = push(*out_stack, lex_pointer);
			lex_pointer = keep;
		}
	}
	operators_stack = push(operators_stack, new_lexem);
	return operators_stack;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////возвращает список в польской записи или NULL  если:  добавляется переменная  
struct Lexem* make_postfixf(struct var** variable_tree_root , char *line ,int *current_s) {

	int  brackets_count = 0, success = 1 , check_operation = 2;// success = 0 - ошибка 
	struct Lexem* out_stack = NULL, *operators_stack = NULL, *new_lexem = NULL ,  *prev_lexem = NULL;
	char lexem , isnumber;//проверка на считывание очередного числа


	while (1) {

		isnumber = 0;
		lexem = line[++(*current_s)];
		if (lexem == '\0') break;

		if (brackets_count < 0) {
			printf("Wrong brackets!!!\n");
			success = 0; 
			break;
		}

		new_lexem = (struct Lexem*)malloc(sizeof(struct Lexem));//новая лехема
		new_lexem->simbol = lexem;
		
		if(isdigit(lexem)) { //обработка чисел
			if(check_operation == 0){
				check_operation = 1;
				free(new_lexem);
				break;
			}
			int number = 0;
			isnumber = 1;
			while (isdigit(lexem)) {
				number *= 10;
				number += lexem - '0';
				(*current_s)++;
				lexem = line[(*current_s)];
				if (line[(*current_s)] == '\0') break;			
			}
			new_lexem->number = number;
			new_lexem->simbol = 0;
			out_stack = push(out_stack, new_lexem);
			prev_lexem = new_lexem;
			check_operation = 0;
			if (line[(*current_s)] == '\0') break;
		}
		
		if(!isdigit(lexem) && lexem != '\0'){///*******

			if (isnumber){//если предыдущая лексема - число , создаем новую лексему
				new_lexem = (struct Lexem*)malloc(sizeof(struct Lexem));
				new_lexem->simbol = lexem;
			}

			if ( new_lexem->simbol == '-') { //  унарный минус(пушим в стэк -1 и умножение)
					if(!prev_lexem || (prev_lexem && prev_lexem->simbol && prev_lexem->simbol!=')') ){//prev_lexem->simbol - всех числовых лексем символы = 0
						check_operation = 1;
						new_lexem->simbol = '*';
						new_lexem->prior = 2;
						prev_lexem = (struct Lexem*)malloc(sizeof(struct Lexem));// new lexem -1
						prev_lexem->simbol = 0;
						prev_lexem->number = -1;
						out_stack = push(out_stack, prev_lexem);
						prev_lexem = new_lexem;
						operators_stack = remove_operator(operators_stack, new_lexem, &out_stack);
						continue;
				    }		  
			}
			int isOperation = 0;
			if (lexem == '(') {//просто пушим '('  в стэк
				brackets_count++;
				new_lexem->prior = 0;
				operators_stack = push(operators_stack, new_lexem);
			}else {// проверка символов операций и переменных

				switch (lexem)
				{
				case '+':new_lexem->prior = 1;isOperation = 1;break;
				case '-':new_lexem->prior = 1;isOperation = 1;break;
				case '*':new_lexem->prior = 2;isOperation = 1; break;
				case '/':new_lexem->prior = 2;isOperation = 1;  break;
				case '%': new_lexem->prior = 2;isOperation = 1;  break;
				case '=':success = 0; free(new_lexem);new_lexem = NULL;
						break;
				case ')':
						isOperation = 0;
						new_lexem->prior = 0;
						brackets_count--;
						if (prev_lexem && prev_lexem->simbol) {
							printf("Wrong brackets!!!\n");
							success = 0;
							free(new_lexem);
							new_lexem = NULL;
						}
						break;	
				default://проверка и добавление новых переменных
						if (new_lexem->simbol != ' ') {//если пробел удаляем лексему
							struct var* variable = set_variable(variable_tree_root , line , current_s);//функция обработки переменных
							if(!variable){
								delete_stack(operators_stack);
	                            delete_stack(out_stack);
	                            free(new_lexem);
	                            return NULL;
							}
							if(variable->assign){
								 delete_stack(operators_stack);
							     delete_stack(out_stack);
							     free(new_lexem);
							     return NULL;
							}else{//если не происходило присваивание - добавить в стэк значение переменной
								   check_operation = 0;
	                               new_lexem->number = variable->value;
					               new_lexem->simbol = 0;
					               out_stack = push(out_stack, new_lexem);
					               prev_lexem = new_lexem;
					               (*current_s) = (*current_s) - 2;/////////////////
					               continue;
							}

						}
                        free(new_lexem);
						new_lexem = NULL;
				}
				if(check_operation && isOperation){
					free(new_lexem);
					break;
				}
				if(!check_operation)
				check_operation = isOperation;

				if (new_lexem) {
					if (new_lexem->simbol == ')') {
						if(brackets_count < 0){
							printf("Wrong brackets!!!\n");
							success = 0;
							break;
						}
						operators_stack = remove_operator(operators_stack, new_lexem, &out_stack);
						continue;
					}
					else {
						operators_stack = remove_operator(operators_stack, new_lexem, &out_stack);//если операция: добавить оператор в стэе операторов
					}
				} else continue;

			}
		}///************

		  prev_lexem = new_lexem;//сохранение предыдущей лексемы
		  if (lexem == '\0') break;
	}

    ////////проверка программы на корректное завершение и очистка стэка операторов
    if(check_operation){
    	success = 0; printf("Not enough arguments\n");
    }
	if (brackets_count && success) {
		success = 0; printf("Wrong brackets!!!\n");
	}
	struct Lexem* keep;

	while (operators_stack) {
		keep = operators_stack->next;;
		out_stack = push(out_stack, operators_stack);
		operators_stack = keep;
	}

	reverse(&out_stack);
	if(success){
         return out_stack;
	}
	else {
		printf("Error\n");
		delete_stack(out_stack);
		delete_stack(operators_stack);
		return NULL;
	}

}