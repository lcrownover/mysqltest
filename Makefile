all:
	@gcc -o main main.c -Wall 

run: all
	@./main
