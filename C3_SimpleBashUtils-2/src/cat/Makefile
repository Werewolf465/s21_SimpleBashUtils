all: s21_cat
s21_cat:
	gcc -std=c11  -Wall -Werror -Wextra  s21_cat.c -o  s21_cat
	
rebuild:
	make clean
	make s21_cat
	
clean:
	rm -rf *.o
	rm -rf s21_cat
