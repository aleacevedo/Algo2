#ifndef CADENA_H
#define CADENA_H

#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si ‘sep’ es '\0'.
 */
char** split(const char* str, char sep);



#endif // CADENA_H
