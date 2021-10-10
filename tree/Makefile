all : tree

factor : tree.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 -Wvla tree.c -o tree -lm

clean :
	rm -f tree