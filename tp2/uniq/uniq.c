#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool contar_palabras(hash_t* hash, char**palabras){
  int i=0;
  while(palabras[i]){
    if(hash_pertenece(hash,palabras[i])){
      int* cant = hash_obtener(hash,palabras[i],cant)
      *cant++;
    else{
      int* cant=calloc(sizeof(int),1);
      if(!cant) return false;
      *cant=1;
      if(!hash_guardar(hash, palabras[i],cant)) return false;
      }
    }
    i++;
  }
}

int main(int argc, char const *argv[]) {
  if (argc!=2) printf("%s\n", "Error en los argumentos"); return -1;
  if (strcmp(argv[0],"-c")==0 || strcmp(argv[1],"-c")==0){
    archivo = FILE * argv[0];
    if(!fopen(archivo)){
      archivo = FILE * argv[1];
      if (!fopen(archivo)) printf("%s\n", "No se pudo abrir el archivo"); return -1;
    }
    hast_t* hash= hash_crear(free);
    while(true){
      char *linea=NULL;
      size_t capacidad=0;
      site_t longitud = getline(&linea, &capacidad, archivo_p);
      if (longitud == -1) break;
      char**palabras = split(linea," ");
      contar_palabras(hash,palabras);
      free(linea);
      }
    hash_iter_t* iter = hash_iter_crear(hash);
    while(!hash_iter_al_final(hash)){
      char* clave = hash_iter_ver_actual(hash)
      int* cant = hash_obtener(hash,clave);
      printf("%i\t %s\n",cant,clave);
    }
    hash_iter_destruir(iter);
    hash_destruir(hash);

  }
  return 0;
}
