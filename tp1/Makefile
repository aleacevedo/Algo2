compile:
	clear
	clear
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c pila/pila.c -o pila.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c cola/cola.c -o cola.o
	gcc -g -std=gnu99 -Wall -Wconversion -Wno-sign-conversion -Werror -c cadena.c -o cadena.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror paste.c -o paste
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror more.c -o more
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror dc.c pila.o cola.o -o dc
	gcc -g -std=gnu99 -Wall -Wconversion -Wno-sign-conversion -Werror main.c cadena.o -o main
	#./paste test1.txt test2.txt
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./main
