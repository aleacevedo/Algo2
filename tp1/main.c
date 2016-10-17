#include"cadena.h"

char** split(const char* str, char sep);

int main(){
  char *str = {"abc,def,ghi"};
  char **strsplit;
  char *nwstr = NULL;
  int i = 0;
  printf("%s\n", str);
  strsplit = split(str, ',');
  while(strsplit[i]!=NULL){
    printf("%i ",i);
    printf("%s\n", strsplit[i]);
    //free(strsplit[i]);
    i++;
  }
  nwstr = join(strsplit, ';');
  printf("%s\n",nwstr); 
  free(strsplit);
  return 0;
}
