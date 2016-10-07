#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool leer_linea(FILE *archivo, char** linea){
  size_t capacidad = 0;
  size_t longitud = getline(linea, &capacidad, archivo);
  if(longitud==-1){
    return false;
  }
  return true;
}

int main(int argc, char* argv[]){
  FILE *archivo = fopen(argv[1], "rt");
  char *linea = NULL;
  if(archivo==NULL){
    return 1;
  }
  for(int i = 0; i<atoi(argv[2]); i++){
    if(!leer_linea(archivo, &linea)){
      free(linea);
      break;
    }
    printf("%s", linea);
    free(linea);
  }
  getchar();
  while(leer_linea(archivo, &linea)){
    printf("%s", linea);
    free(linea);
    getchar();
  }
  free(linea);
  return 0;
}
