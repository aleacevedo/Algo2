#include"strutil.h"

char** split(const char* str, char sep);

int main(){
  char *str = {","};
  char **strsplit;
  char *nwstr = NULL;
  int i = 0;
  printf("%s\n", str);
  strsplit = split(str, ',');
  while(strsplit[i]!=NULL){
    printf("%s\n", strsplit[i]);
    i++;
  }
  nwstr = join(strsplit, ';');
  printf("%s\n",nwstr);
  free_strv(strsplit);
  free(nwstr);
  return 0;
}
