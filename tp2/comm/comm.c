#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool leer_lineas(hash_t* hash, const char* archivo, int valor_act){
  FILE* archivo_p;
  archivo_p = fopen(archivo, "r");
  if (!archivo_p){
    printf("%s %s\n", "Error al abrir: ", archivo);
    return false;
  }
  while(true){
    char *linea = NULL;
    size_t capacidad = 0;
    size_t longitud = getline(&linea, &capacidad, archivo_p);
    if (longitud == -1){
      free(linea);
      fclose(archivo_p);
      return true;
    }
    int* valor = calloc(sizeof(int),1);
    if(hash_pertenece(hash, linea)){
      int* val = hash_obtener(hash, linea);
      if(*val != valor_act){
        *valor = 3;
        if(!hash_guardar(hash,linea,valor)){
          free(linea);
          fclose(archivo_p);
         return false;
        }
      }
    }
    else{
      *valor = valor_act;
      if(!hash_guardar(hash,linea,valor)){
      free(linea);
      fclose(archivo_p);
      return false;
      }
    }
    free(linea);
  }
  fclose(archivo_p);
  return true;
}
int main(int argc, char const *argv[]) {
  if(argc<3){
    printf("%s\n", "Muy pocos argumentos");
    return -1;
  }
  const char* ARCHIVO_1 = NULL;
  const char* ARCHIVO_2 = NULL;
  const char* archivo_actual;
  ARCHIVO_1 = argv[1];
  ARCHIVO_2 = argv[2];
  hash_t* hash=hash_crear(free);
  archivo_actual = ARCHIVO_1;
  leer_lineas(hash,archivo_actual,1);
  archivo_actual = ARCHIVO_2;
  leer_lineas(hash,archivo_actual,2);
  hash_iter_t* iter=hash_iter_crear(hash);
  while(!hash_iter_al_final(iter)){
    const char* linea=hash_iter_ver_actual(iter);
    int* val = hash_obtener(hash,linea);
    if(argc < 4 ){
      if(*val==3){
        printf("%s\n", linea);
      }
    }
    else{
      if(strcmp(argv[3], "-1")==0 && *val == 1){
        printf("%s\n", linea);
      }
      if (strcmp(argv[3], "-2")==0 && *val == 2) {
        printf("%s\n", linea);
      }
    }
    hash_iter_avanzar(iter);
  }
  hash_iter_destruir(iter);
  hash_destruir(hash);
  return 0;
}
