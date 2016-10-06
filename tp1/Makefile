compile:
	clear
	clear
	clear
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror paste.c -o paste
	#./paste test1.txt test2.txt
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./paste test1.txt test2.txt
