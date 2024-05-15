all: s21_grep
s21_grep:
	gcc -std=c11  -Wall -Werror -Wextra  s21_grep.c -o  s21_grep
	
rebuild:
	make clean
	make s21_grep
	
clean:
	rm -rf *.o
	rm -rf s21_grep
