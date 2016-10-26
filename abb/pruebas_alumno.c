#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "testing.h"
#include <time.h>

bool imprimir_claves(const char* clave, void *dato, void *extra){
  if (clave) {
    printf("%s\n", clave);
    return true;
  }
  return false;
}

void prueba_abb_vacio(){
 abb_t *abb = abb_crear(strcmp, free);
 free(abb);
}


static void prueba_abb_volumen(size_t largo, bool debug)
{
    abb_t* abb = abb_crear(strcmp,free);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    unsigned* valores[largo];
    /* Inserta 'largo' parejas en el hash */
    bool ok = true;
    srand(125);
    for (unsigned i = 0; i < largo; i++) {
      valores[i] = malloc(sizeof(int));
      sprintf(claves[i], "%08d", rand()%10);
      *valores[i] = i;
        if(!(abb_pertenece(abb, claves[i]))){
          ok = abb_guardar(abb, claves[i], valores[i]);
        }
        if (!ok) break;
    }
    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    for (size_t i = 0; i < largo; i++) {
        unsigned *b;
        if((abb_pertenece(abb,claves[i]))){
          b = (unsigned *)abb_borrar(abb, claves[i]);
          ok = (b == valores[i]);
        }
        free(valores[i]);
        if (!ok) break;
    }
    if (debug) print_test("Prueba hash borrar muchos elementos", ok);
    free(claves);
    abb_destruir(abb);

}

void pruebas_abb_alumno(){
  prueba_abb_vacio();
  prueba_abb_volumen(10, true);
}
