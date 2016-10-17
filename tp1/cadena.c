#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char** split(const char* str, char sep){
  char* aux = "\0";
  size_t cont = 0;
  char** strv = malloc(sizeof(char*));
  char** strvaux = NULL;
  strv[cont] = "\0";
  if(sep=='\0'||strv==NULL){
    return NULL;
  }
  for(int i = 0; i<=strlen(str); i++){
    if(str[i]==sep){
      strv[cont] = strdup(aux);
      cont++;
      strvaux = realloc(strv, sizeof(char*)*(cont+1));
      if(strvaux==NULL){
        return NULL;
      }
      strv = strvaux;
      aux = "\0";
      //strv[cont] = NULL;
    }
    else{
      aux = strcat(aux,&str[i]);
    }
  }
  strv[cont] = strdup(aux);
  cont++;
  strvaux = realloc(strv, sizeof(char*)*(cont+1));
  if(strvaux==NULL){
    return NULL;
  }
  strv = strvaux;
  strv[cont] = NULL;
  return strv;
}
