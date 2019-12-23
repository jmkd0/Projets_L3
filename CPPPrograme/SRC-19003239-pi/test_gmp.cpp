#include <iostream>
#include <vector>
#include <math.h>
#include <gmp.h>
using namespace std;
long val_precision=1000;

void calcule_pi_approche(mpf_t pi, long n){
    mpf_t v1;
    mpf_set_default_prec(val_precision);
    mpf_init_set_d(pi,0); 
    mpf_init_set_d(v1,1);
    for(int k=0; k<=n; k++){
        mpf_t  a,b,c,d,v16;     mpf_init_set_d(v16,16);
        mpf_init_set_d(a,8);    mpf_init_set_d(b,8);   mpf_init_set_d(c,8); mpf_init_set_d(d,8); 
        mpf_mul_ui(a,a,k);      mpf_mul_ui(b,b,k);     mpf_mul_ui(c,c,k);   mpf_mul_ui(d,d,k);
        mpf_add_ui(a,a,1);      mpf_add_ui(b,b,4);     mpf_add_ui(c,c,5);   mpf_add_ui(d,d,6);
        mpf_div(a,v1,a);        mpf_div(b,v1,b);       mpf_div(c,v1,c);     mpf_div(d,v1,d);
        mpf_mul_ui(a,a,4);      mpf_mul_ui(b,b,2);
        mpf_sub(a,a,b);         mpf_sub(a,a,c);        mpf_sub(a,a,d);
        mpf_pow_ui(v16,v16,k);  mpf_div(v16,v1,v16);
        mpf_mul(a,a,v16);
        mpf_add(pi,pi,a);
        mpf_clear(a);   mpf_clear(b);   mpf_clear(c);   mpf_clear(d);   mpf_clear(v16);
    }
}

int main(){
    long limite_pi;
    cout<<"Entrer la limite des décimales de pi: "; cin>>limite_pi; 
 
mp_exp_t exp;
    char* str;
    mpf_set_default_prec(val_precision);
    mpf_t pi;
    mpf_init(pi);
    calcule_pi_approche(pi,limite_pi);
    gmp_printf("val= %.*Ff",limite_pi,pi);

    return 0;
}
