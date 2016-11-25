compile:
	gcc -g -std=c99 -Wall -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -c -o heap.o heap.c
	gcc -g -std=c99 -Wall -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -c -o testing.o testing.c
	gcc -g -std=c99 -Wall -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -c -o pruebas.o pruebas.c
	gcc -g -std=c99 -Wall -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -c -o heap.o testing.o pruebas.o
	gcc -g -std=c99 -Wall -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -o prueba heap.o testing.o pruebas.o main.c
run:
	valgrind --leak-check=full --main-stacksize=1 --track-origins=yes --show-reachable=yes ./prueba
