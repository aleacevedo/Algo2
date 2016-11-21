#include "heap-utils.h"
#include <stdlib.h>
#include <stdio.h>
int comp_ent(const void *a, const void *b){
  if(*(int*)a<*(int*)b){
    return -1;
  }
  if(*(int*)a>*(int*)b){
    return 1;
  }
  return 0;
}

int main(){
  int largo = 10;
  void** valores = malloc(largo*sizeof(void*));
  void** res;
  int valor[largo];
  for(int i = 0; i<largo; i++){
    valor[i] = i;
    valores[i] = &valor[i];
  }
  res = top_k(14, valores, largo, comp_ent);
  for(int i = 0; i<14; i++){
    if(res[i])printf("TOP %i\n", *(int*)res[i]);
    else printf("NULL\n");
  }
  free(res);
}
