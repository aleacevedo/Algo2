#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila/pila.h"

typedef struct linea{
  char *caracteres;
  size_t largo;
}linea_t;

int main(){
  linea_t *linea = calloc(1,sizeof(linea_t));
  linea->caracteres = calloc(1, sizeof(char));
  linea->largo = 1;
  char entrada;
  while(true){
    char  *aux;
    scanf("%s", &entrada);
    printf("%c\n", entrada);
    printf("entrada %zu, char %zu\n", sizeof(entrada), sizeof(char));
    linea->caracteres[linea->largo-1] = entrada;
    linea->largo+=1;
    aux=realloc(linea->caracteres, sizeof(char)*linea->largo);
    if(aux==NULL){
      printf("TENEMOS UN PROBLEMA\n");
      break;
    }
    linea->caracteres = aux;
  }
  free(linea->caracteres);
  free(linea);
}
