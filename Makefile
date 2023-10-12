all:
	gcc -o main main.c -Wall -L/usr/lib64/ -lmariadb

run: all
	./main
