/*
 * prueba_hash.c
 * Pruebas para el tipo de dato abstracto Tabla de Hash
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */

#include "hash.h"
#include "testing.h"
#include "fnv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

static void prueba_crear_hash_vacio_alumno()
{
    hash_t* hash = hash_crear(NULL);

    print_test("Prueba hash crear hash vacio", hash);
    //print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);
    //print_test("Prueba hash obtener clave A, es NULL, no existe", !hash_obtener(hash, "A"));
    //print_test("Prueba hash pertenece clave A, es false, no existe", !hash_pertenece(hash, "A"));
    print_test("Prueba hash borrar clave A, es NULL, no existe", !hash_borrar(hash, "A"));

    //hash_destruir(hash);
}
static void prueba_crear_hash_uno_alumno()
{
    hash_t* hash = hash_crear(NULL);
    int i = 5;
    //void *punt = &i;
    const char clave1[5]={'H','O','L','A','\0'};
    const char clave2[5]={'H','O','L','P','\0'};
    print_test("Prueba hash crear hash vacio", hash);
    print_test("Prueba insertar 1", hash_guardar(hash,clave1,&i));
    print_test("Prueba borra nada", !hash_borrar(hash,clave2));
    print_test("Prueba borra 1", hash_borrar(hash,clave1)==&i);


    //print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);
    //print_test("Prueba hash obtener clave A, es NULL, no existe", !hash_obtener(hash, "A"));
    //print_test("Prueba hash pertenece clave A, es false, no existe", !hash_pertenece(hash, "A"));
    print_test("Prueba hash borrar clave A, es NULL, no existe", !hash_borrar(hash, "A"));

    //hash_destruir(hash);
}


void pruebas_hash_alumno(){
  prueba_crear_hash_vacio_alumno();
  prueba_crear_hash_uno_alumno();
}
