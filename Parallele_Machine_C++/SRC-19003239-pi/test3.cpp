#include <iostream>
#include <math.h>
#include <gmp.h>
using namespace std;
int main(){
 
 double c=11;
 double d=3;
	mpf_t m, v1;mpf_t n;mpf_t p;
  mpz_t h;
  mp_exp_t exp;
  char* str;

	mpf_set_default_prec(1000);
  mpz_init_set_ui(h,2);
  mpf_init_set_d(m,22); 
  mpf_div_ui(m,m,7);
  
//  mpz_get_str(str,10,h);
 //char * mpf_get_str (char *str, mp_exp_t *expptr, int base, size_t n_digits, const mpf_t op);
  str=mpf_get_str(NULL,&exp,10,52,m);
	//gmp_printf("\nm=%.*Ff",40,m);
  gmp_printf("\nstr= %s",str);
  cout<<endl<<str;
	mpf_clear(m);
  return 0;
}