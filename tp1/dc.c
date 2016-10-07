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
  char *guardado;
  while(true){
    char  *aux;
    scanf("%c", &entrada);
    printf("%c\n", entrada);
    if(letra=='\n'){
     linea->largo--;
     break;
    }
    //printf("entrada %zu, char %zu\n", sizeof(entrada), sizeof(char));
    linea->caracteres[linea->largo-1] = entrada;
    linea->largo+=1;
    aux=realloc(linea->caracteres, sizeof(char)*linea->largo);
    if(aux==NULL){
      printf("TENEMOS UN PROBLEMA\n");
      break;
    }
    linea->caracteres = aux;
  }
  for(int i = 0;i<linea->largo; i++){
   if(linea->caracteres[i]==' '){
     f
  free(linea->caracteres);
  free(linea);
}
