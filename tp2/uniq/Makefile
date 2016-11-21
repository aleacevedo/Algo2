compile:
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c fnv.c -o fnv.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c hash.c -o hash.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -c strutil.c -o strutil.o
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror  uniq.c hash.o fnv.o strutil.o -o pruebas
	./pruebas archivo.txt -c

valgrind:
	valgrind --leak-check=full --main-stacksize=1 --track-origins=yes --show-reachable=yes ./pruebas archivo.txt -c
