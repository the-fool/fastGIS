#include <stdlib.h>
#include <stdio.h>

void f(char *p);

int main()
{
  // printf("%s\n", getenv("FASTGIS_PATH"));
  char *env = getenv("FASTGIS_PATH");
  f(env);
  return 0;
}

void f(char *p)
{
  printf("%s\n", p);
}
