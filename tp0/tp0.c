#include "tp0.h"
#include <stdio.h>
/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	int pos = 0;
	if(n==0){
		return -1;
	}
	else{
		for(int i = 0; i<n; i++){
			if (vector[i]>vector[pos]){
				pos = i;
			}
		}
		return pos;
	}
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	if(n1 < n2){
		printf("N1: %i \n", n1);
		printf("N2: %i \n", n2);
		for (int i = 0; i<n1; i++){
			if(vector1[i]<vector2[i]){
				printf("-1");
				return -1;
			}
			if(vector2[i]<vector1[i]){
				printf("1");
				return 1;
			}
		}
		return -1;
	}
	else if(n2<n1){
		for (int i = 0; i<n2; i++){
			if(vector1[i]<vector2[i]){
				return -1;
			}
			if(vector2[i]<vector1[i]){
				return 1;
			}
			return 1;
		}
	}
	else{
		for (int i = 0; i<n1; i++){
			if(vector1[i]<vector2[i]){
				return -1;
			}
			if(vector2[i]<vector1[i]){
				return 1;
			}
		}
	}
	return 0;
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	int p;
	p = maximo(vector,n);
	while(p!=-1){
		vector[n-1]=vector[p];
		n=n-1;
		p = maximo(vector,n);
	}
}
