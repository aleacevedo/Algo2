#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool leer_lineas(hast_t* hash, char* archivo){
  if (!fopen(archivo)) printf("%s %s\n", "Error al abrir: ", archivo); return false;
  while(true){
    char *linea = NULL;
    size_t capacidad = 0;
    site_t longitud = getline(&linea, &capacidad, archivo_p);
    if (longitud == -1) return true;
    int* valor=calloc(sizeof(int),1);
    if(hash_pertenece(hash, linea)){
      if(hash_obtener(hash, linea) != ARCHIVO_ACTUAL){
        *valor = AMBOS;
        hash_guardar(hash,linea,valor);
      }
    }
    *valor = ARCHIVO_ACTUAL;
    if(!hash_guardar(hash,linea,valor)) return false;
  }
}
int main(int argc, char const *argv[]) {
  if(argc<2) printf("%s\n", "Muy pocos argumentos"); return -1;
  archivo1 = FILE* argv[0];
  archivo2 = FILE* argv[1];
  if (!fopen(archivo1)) printf("%s %s\n", "Error al abrir: ",argv[0]); return -1;
  if (!fopen(archivo2)) printf("%s %s\n", "Error al abrir: ",argv[1]); return -1;
  hash_t* hash=hash_crear(free);
  archivo_actual = ARCHIVO_1;
  while(leer_linea(hash,archivo1,archivo_actual)){
    continue;
  }
  archivo_actual = ARCHIVO_2
  while (leer_linea(hash,archivo2,archivo_actual)) {
    continue;
  }
  hash_iter_t* iter=hash_iter_crear(hash);
  while(!hash_iter_al_final(iter)){
    char* linea=hash_iter_ver_actual(iter);
    if(argc < 3 && hash_obtener(hash,linea) == AMBOS) printf("%s\n", linea);
    if(strcmp(argv[2], "-1" && hash_obtener(hash, linea) == ARCHIVO_1) printf("%s\n", linea);
    if (strcmp(argv[2], "-2") && hash_obtener(hash, linea) == ARCHIVO_2) printf("%s\n", linea);
    }
  }
  hash_iter_destruir(iter);
  hash_destruir(hash); 
  return 0;
}
