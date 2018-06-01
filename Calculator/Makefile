
start: sourse.o avl_var_tree.o api.o calculate.o api.h
	gcc -Wall -Wextra -Wshadow   -o start sourse.o avl_var_tree.o api.o calculate.o

sourse.o: sourse.c
	gcc -Wall -Wextra -Wshadow -c  sourse.c

avl_var_tree.o: avl_var_tree.c
	gcc -Wall -Wextra -Wshadow -c avl_var_tree.c

api.o: api.c api.h
	gcc -Wall -Wextra -Wshadow -c  api.c

calculate.o: calculate.c calculate.h api.h
	gcc -Wall -Wextra -Wshadow -c  calculate.c

clean:
	rm -rf *.o	



