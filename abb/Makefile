compile:

	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c abb.c -o abb.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c abb_test-0.2/abb_aux.c abb.o -o abb_test-0.2/abb_aux.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c testing.c -o testing.o
	##gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pruebas_catedra.c -o pruebas_catedra.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pruebas_alumno.c -o pruebas_alumno.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror  main.c abb.o testing.o pruebas_alumno.o -o pruebas
	##./pruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
