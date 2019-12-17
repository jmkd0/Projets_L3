#include <stdio.h>

int fact (int n)
{
  if (n == 0 || n == 1) return 1;
  return n * fact(n - 1);
}

int factloop (int n)
{
  int r = 1;
  while (n > 0) {
    r = n * r;
    n = n - 1
  }
  return r;
}

int main ()
{
  int num;
  printf("n? ");
  scanf("%d", &num);
  printf("n! = ");
  printf("%d", fact(num));
  printf("\n");
  return 0;
}
