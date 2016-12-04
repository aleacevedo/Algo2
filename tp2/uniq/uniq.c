#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool contar_palabras(hash_t* hash, char**palabras){
  int i=0;
  int *cant;
  while(palabras[i]){
    if(hash_pertenece(hash,palabras[i])){
      cant = hash_obtener(hash,palabras[i]);
      *cant+=1;
    }
    else{
      int* cant=calloc(sizeof(int),1);
      if(!cant) return false;
      *cant=1;
      if(!hash_guardar(hash, palabras[i],cant)) return false;
      }
      i++;
    }
    return true;
  }

int main(int argc, char const *argv[]) {
  if (argc != 3){
    printf("%s\n", "Error en los argumentos");
    return -1;
  }
  if (strcmp(argv[1],"-c")==0 || strcmp(argv[2],"-c")==0){
    FILE * archivo_p;
    archivo_p = fopen(argv[1],"r");
    if(! archivo_p){
      archivo_p = fopen(argv[2],"r");
      if (!archivo_p) printf("%s\n", "No se pudo abrir el archivo"); return -1;
    }
    hash_t* hash= hash_crear(free);
    while(true){
      char *linea=NULL;
      size_t capacidad=0;
      ssize_t longitud = getline(&linea, &capacidad, archivo_p);
      if (longitud == -1) break;
      linea[longitud-1] = '\0';
      char **palabras = split(linea,' ');
      contar_palabras(hash,palabras);
      free(linea);
      free_strv(palabras);
    }
    fclose(archivo_p);
    hash_iter_t* iter = hash_iter_crear(hash);
    const char* clave;
    while(!hash_iter_al_final(iter)){
      clave = hash_iter_ver_actual(iter);
      int* cant = hash_obtener(hash,clave);
      printf("%i\t %s\n",*cant,clave);
      hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    hash_destruir(hash);

  }
  else{
    printf("%s\n", "falta la instruccion -c");
  }
  return 0;
}
