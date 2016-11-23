#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "testing.h"
#include <time.h>

bool imprimir_claves(const char* clave, void *dato, void *extra){
  if(clave){
    printf("%s\n", clave);
    return true;
  }
  else{
    return false;
  }
}

int* crear_claves(int **claves_ord){
  int *claves = malloc(sizeof(int)*12);
  *claves_ord = malloc(sizeof(int)*12);
  (*claves_ord)[0] = 1;
  (*claves_ord)[1] = 3;
  (*claves_ord)[2] = 5;
  (*claves_ord)[3] = 8;
  (*claves_ord)[4] = 9;
  (*claves_ord)[5] = 10;
  (*claves_ord)[6] = 12;
  (*claves_ord)[7] = 15;
  (*claves_ord)[8] = 16;
  (*claves_ord)[9] = 17;
  (*claves_ord)[10] = 19;
  (*claves_ord)[11] = 20;
  claves[0] = 10;
  claves[1] = 8;
  claves[2] = 15;
  claves[3] = 9;
  claves[4] = 12;
  claves[5] = 17;
  claves[6] = 3;
  claves[7] = 1;
  claves[8] = 5;
  claves[9] = 16;
  claves[10] = 20;
  claves[11] = 19;
  return claves;
}

void prueba_abb_vacio(){
 abb_t *abb = abb_crear(strcmp, free);
 abb_destruir(abb);
}

void prueba_abb_pisar(){
  printf("\n////////////PRUEBA ABB PISAR///////////\n");
  abb_t* abb = abb_crear(strcmp,free);
  const size_t largo_clave = 10;
  size_t largo = 12;
  char (*claves)[largo_clave] = malloc(largo * largo_clave);
  unsigned* valores[largo];
  bool ok = true;
  int *clave_ord;
  int *clave = crear_claves(&clave_ord);
  for (unsigned i = 0; i < largo; i++) {
    sprintf(claves[i], "%08d", clave[i]);
    valores[i] = malloc(sizeof(int));
    *valores[i] = i;
    ok = abb_guardar(abb, claves[i], valores[i]);
    if (!ok) break;
  }
  print_test("Prueba abb almacenar 12 elementos", ok);
  for (unsigned i = 0; i < largo; i++) {
    sprintf(claves[i], "%08d", clave_ord[i]);
    valores[i] = malloc(sizeof(int));
    *valores[i] = 10;
    ok = abb_guardar(abb, claves[i], valores[i]);
    if (!ok) break;
  }
  print_test("Prueba abb piso 12 elementos", ok);
  for (size_t i = 0; i < largo/2; i++) {
      unsigned *b;
      if((abb_pertenece(abb,claves[i]))){
        b = (unsigned *)abb_borrar(abb, claves[i]);
        ok = (*b == 10);
        free(valores[i]);
      }
      if (!ok) break;
  }
  print_test("Prueba borrar mitad pisados", ok);
  free(claves);
  free(clave);
  free(clave_ord);
  abb_destruir(abb);
}


void prueba_abb_iter(){
  printf("\n////////////PRUEBA ABB ITER///////////\n");
  abb_t* abb = abb_crear(strcmp,free);
  const size_t largo_clave = 10;
  size_t largo = 12;
  char (*claves)[largo_clave] = malloc(largo * largo_clave);
  unsigned* valores[largo];
  bool ok = true;
  int *clave_ord;
  abb_iter_t *iter;
  int h = 0;
  int *clave = crear_claves(&clave_ord);
  for (unsigned i = 0; i < largo; i++) {
    sprintf(claves[i], "%08d", clave[i]);
    if(!abb_pertenece(abb, claves[i])){
      valores[i] = malloc(sizeof(int));
      *valores[i] = i;
      ok = abb_guardar(abb, claves[i], valores[i]);
      unsigned int a = *(unsigned int*)valores[i];
      printf("Clave: %s Valor: %u\n", claves[i], a);
    }
    if (!ok) break;
  }
  print_test("Prueba abb almacenar 12 elementos", ok);
  iter = abb_iter_in_crear(abb);
  while(!abb_iter_in_al_final(iter)){
    sprintf(claves[h], "%08d", clave_ord[h]);
    ok = strcmp(claves[h],abb_iter_in_ver_actual(iter))==0;
    h++;
    abb_iter_in_avanzar(iter);
  }
  print_test("Prueba recorrer in order", ok);
  free(claves);
  free(clave);
  free(clave_ord);
  abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

 void prueba_iter_post(){
   printf("%s\n","PRUEBA ITER POST ORDER");
   int extra;
   abb_t* abb = abb_crear(strcmp,free);
   const size_t largo_clave = 10;
   size_t largo = 12;
   char (*claves)[largo_clave] = malloc(largo * largo_clave);
   unsigned* valores[largo];
   bool ok = true;
   int *clave_ord;
   //abb_iter_t *iter;
   //int h = 0;
   int *clave = crear_claves(&clave_ord);
   for (unsigned i = 0; i < largo; i++) {
     sprintf(claves[i], "%08d", clave[i]);
     if(!abb_pertenece(abb, claves[i])){
       valores[i] = malloc(sizeof(int));
       *valores[i] = i;
       ok = abb_guardar(abb, claves[i], valores[i]);
       unsigned int a = *(unsigned int*)valores[i];
       printf("Clave: %s Valor: %u\n", claves[i], a);
     }
     if (!ok) break;
   }
   print_test("Prueba abb almacenar 12 elementos", ok);
   printf("%s\n", "imprimir POST ORDER EXTERNO");
   abb_post_order(abb, imprimir_claves,&extra);
   printf("%s\n", "imprimir POST ORDER INTERNO");
   abb_iter_post_t* iter_post = abb_iter_post_crear(abb);
   while(!abb_iter_post_al_final(iter_post)){
     printf("Actual %s\n", abb_iter_post_ver_actual(iter_post));
     abb_iter_post_avanzar(iter_post);
   }
   free(claves);
   free(clave);
   free(clave_ord);
   abb_iter_post_destruir(iter_post);
   abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo, bool debug){
    printf("\n////////////PRUEBA ABB VOLUMEN///////////\n");
    abb_t* abb = abb_crear(strcmp,free);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    unsigned* valores[largo];
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
      sprintf(claves[i], "%08d", rand()%10000);
      if(!abb_pertenece(abb, claves[i])){
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
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
          free(valores[i]);
        }
        if (!ok) break;
    }
    if (debug) print_test("Prueba hash borrar muchos elementos", ok);
    free(claves);
    abb_destruir(abb);
}

void prueba_abb_items() {
  abb_t* abb = abb_crear(strcmp,free);
  const size_t largo_clave = 10;
  size_t largo = 12;
  char (*claves)[largo_clave] = malloc(largo * largo_clave);
  unsigned* valores[largo];
  bool ok = true;
  int *clave_ord;
  int *clave = crear_claves(&clave_ord);
  for (unsigned i = 0; i < largo; i++) {
    sprintf(claves[i], "%08d", clave[i]);
    if(!abb_pertenece(abb, claves[i])){
      valores[i] = malloc(sizeof(int));
      *valores[i] = i;
      ok = abb_guardar(abb, claves[i], valores[i]);
      unsigned int a = *(unsigned int*)valores[i];
      printf("Clave: %s Valor: %u\n", claves[i], a);
    }
    if (!ok) break;
  }
  print_test("Prueba abb almacenar 12 elementos", ok);
  abb_item_t* items = abb_obtener_items(abb);
  int j = 0;
  while(j<abb_cantidad(abb)){
    printf("Clave = %s\t Valor = %i\n", items[j].clave,*(int*) items[j].valor);
    j++;
  }

}

void pruebas_abb_alumno(){
  prueba_abb_vacio();
  prueba_abb_volumen(1000, true);
  prueba_abb_iter();
  prueba_abb_pisar();
  prueba_iter_post();
  prueba_abb_items();
}
