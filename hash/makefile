compile:
	clear
	clear
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c fnv.c -o fnv.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c hash.c -o hash.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c testing.c -o testing.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pruebas_catedra.c -o pruebas_catedra.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pruebas_alumno.c -o pruebas_alumno.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror  main.c hash.o fnv.o testing.o pruebas_alumno.o pruebas_catedra.o -o pruebas
	./pruebas

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
