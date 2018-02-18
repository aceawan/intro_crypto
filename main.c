#include "main.h"
#include <stdio.h>
#include <gmp.h>

int main(int argc, char* argv){
    mpz_t g;
    mpz_t p;

    // G initialization
    mpz_init(g);
    mpz_set(g, 2);

    // P initialization
    mpz_init(p);
    mpz_set_str(p, P_HEX_VALUE, 16);
    return 0;
}

void euclide(mpz_t a, mpz_t p){

}