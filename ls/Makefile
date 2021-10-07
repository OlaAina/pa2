all : ls

factor : ls.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 -Wvla ls.c -o ls -lm

clean :
	rm -f ls