#ifndef HEAPUTILS_H
#define HEAPUTILS_H
#include "heap-utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp);

#endif // HEAPUTILS_H
