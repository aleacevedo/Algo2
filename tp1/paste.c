#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ENTRADAS_MAX 3

bool leer_linea(char** guardado, size_t* longitud_vieja, FILE *archivo){
  /*Lee una linea del archivo pasado por parametro lo guarda en guardado, si ya
  hay otra linea las separa por un tab pasado por parametro y su longitud en el
   puntero longitud. Si el archivo llego a su fin devuelve false*/
  char *linea = NULL;
  char *aux = NULL;
  size_t capacidad = 0;
  size_t longitud = getline(&linea, &capacidad, archivo);
  if(longitud==-1){
    free(linea);
    return false;
  }
  if(*longitud_vieja!=0){
    aux = realloc(*guardado,longitud+*longitud_vieja);
    if(aux == NULL){
      return false;
    }
    *guardado = aux;
    strcat(*guardado, "\t");
  }
  else{
    *guardado = calloc(longitud, sizeof(char));
    if(guardado == NULL){
      return false;
    }
  }
  linea = strtok(linea, "\n");
  strcat(*guardado, linea);
  free(linea);
  *longitud_vieja = longitud+*longitud_vieja;
  return true;
}

int main(int argc, char* argv[]){
  char *guardado = NULL;
  if(argc!=ENTRADAS_MAX){
    printf("Maximo 2 entradas, NO: %i\n", argc);
    return 1;
  }
  FILE *arch1 = fopen(argv[1], "rt");
  FILE *arch2 = fopen(argv[2], "rt");
  while(true){
    size_t longitud = 0;
    if(!leer_linea(&guardado, &longitud, arch1)){
      if(!leer_linea(&guardado, &longitud, arch2)){
        fclose(arch1);
        fclose(arch2);
        return 0;
      }
      free(guardado);
      fclose(arch1);
      fclose(arch2);
      return -1;
    }
    if(!leer_linea(&guardado, &longitud, arch2)){
      free(guardado);
      fclose(arch1);
      fclose(arch2);
      return -1;
    }
    printf("%s\n",guardado);
    free(guardado);
  }
  return 0;
}
