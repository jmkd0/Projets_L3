#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "gmp.h"
#include <string.h>
using namespace std;

void example(){
  mpz_t a,b,c;
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_set_str(a,"342312532453246435457",10);
  mpz_set_str(b,"346534643743565654456",10);
  mpz_add(c,a,b);// c = a + b;
  gmp_printf("%Zd\n",c);
  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c);
}

int main(int argc, char * argv[]){
  example();
  
  return 0;
}