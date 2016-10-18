#include"cadena.h"

char** split(const char* str, char sep);

int main(){
  char *str = {"ab,jo,lk,"};
  char **strsplit;
  char *nwstr = NULL;
  int i = 0;
  printf("%s\n", str);
  strsplit = split(str, ',');
  while(strsplit[i]!=NULL){
    printf("%s\n", strsplit[i]);
    //free(strsplit[i]);
    i++;
  }
  nwstr = join(strsplit, ';');
  printf("%s\n",nwstr);
  i = 0;
  while(strsplit[i]!=NULL){
    free(strsplit[i]);
    i++;
  }
  free(nwstr);
  free(strsplit);
  return 0;
}
