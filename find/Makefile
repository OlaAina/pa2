all : find

factor : find.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 -Wvla find.c -o find -lm

clean :
	rm -f find