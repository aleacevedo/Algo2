compile:
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c lista.c -o lista.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c ejemplo_iteradores.c -o ejemplo_iteradores.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c testing.c -o testing.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pruebas_alumno.c -o pruebas_alumno.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror  main.c lista.o testing.o pruebas_alumno.o ejemplo_iteradores.o -o pruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
