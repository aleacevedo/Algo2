compile:
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c fnv.c -o fnv.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c hash.c -o hash.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror  comm.c hash.o fnv.o -o pruebas
	./pruebas archivo1.txt archivo2.txt -2

valgrind:
	valgrind --leak-check=full --main-stacksize=1 --track-origins=yes --show-reachable=yes ./pruebas archivo1.txt archivo2.txt -2
