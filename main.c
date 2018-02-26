#include "main.h"
#include <stdio.h>

int main(int argc, char* argv){
    mpz_t g, p, u, v, r;

    // G initialization
    mpz_init(g);
    mpz_set_ui(g, 2);


    // P initialization
    mpz_init_set_str(p, P_HEX_VALUE, 16);
	euclide(r, u, v, g, p);

	mpz_out_str(NULL, 10, u);
	printf(" et ");
	mpz_out_str(NULL, 10, v);
	printf(" et ");
	mpz_out_str(NULL, 10, r);

	printf("\nGCDext:\n");
	mpz_gcdext(r, u, v, g, p);
	mpz_out_str(NULL, 10, u);
	printf(" et ");
	mpz_out_str(NULL, 10, v);
	printf(" et ");
	mpz_out_str(NULL, 10, r);
    return 0;
}

void euclide(mpz_t r0, mpz_t u0, mpz_t v0, mpz_t a, mpz_t p){
	mpz_t r, r1, u, u1, q, v, v1;
	mpz_init(q);
	mpz_init(r);
    mpz_init(r0);
    mpz_set(r0, a);

    mpz_init(r1);
    mpz_set(r1, p);


	mpz_init(u);
    mpz_init(u0);
    mpz_set_ui(u0, 1);
    mpz_init(u1);
    mpz_set_ui(u1, 0);

	mpz_init(v);
	mpz_init(v0);
    mpz_set_ui(v0, 0);
    mpz_init(v1);
    mpz_set_ui(v1, 1);

    // mpz_sgn(r1) renvoie 1 si >0, 0 si == et -1 sinon
	while(mpz_sgn(r1) == 1) {
		//mpz_out_str(NULL, 10, r1);
		//Q := Quotient Division(R0;R1) ;
		//R := Reste Division(R0;R1)
		mpz_tdiv_qr(q, r, r0, r1);

		//U := U0 – Q.U1; V := V0 –Q.V1;
		mpz_set(u, u0);
		mpz_set(v, v0);
		mpz_submul(u, q, u1); // u = u-q*u1
		mpz_submul(v, q, v1); // v = v-q*v1

		//R0 := R1; R1 := R;
		mpz_set(r0, r1);
		mpz_set(r1, r);


		//U0 := U1; U1 := U ;
		mpz_set(u0, u1);
		mpz_set(u1, u);

		//V0 := V1; V1 := V ;
		mpz_set(v0, v1);
		mpz_set(v1, v);
	}
}
