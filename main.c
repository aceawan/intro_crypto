#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * TODO : Supprimer pour le rendu final !!!!!!!!!!!!!!!!!!!!!!!
 * Ma fonction de tests crados
 */
void tests_subtils(){
	mpz_t g, p, u, v, r, a, x, big_x, c, b, m, m0;

    // G initialization
    mpz_inits(g, u, v, r, a, x, big_x, c, b, m, m0,  (void *) NULL);
    mpz_set_ui(g, 2);

	mpz_set_ui(m, 26041995);

    // P initialization
    mpz_init_set_str(p, P_HEX_VALUE, 16);

	printf("Clefs : \n");
	keyGen(x, big_x, p, g);
	printf("Clef publique X : ");
	mpz_out_str(NULL, 10, big_x);
	printf("\nClef privée x : ");
	mpz_out_str(NULL, 10, x);
	printf("\n\n");

	encrypt(c, b, big_x, p, g, m);
	printf("Message m : ");
	mpz_out_str(NULL, 10, m);

	printf("\nChiffrés\n");
	printf("C : ");
	mpz_out_str(NULL, 10, c);
	printf("\nB : ");
	mpz_out_str(NULL, 10, b);
	printf("\n\n");

	decrypt(m0, c, b, x, p);
	printf("Message m déchiffré : ");
	mpz_out_str(NULL, 10, m0);
	printf("\n\n");


/*
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

	*/

	/*
    mpz_inits(a, r);
	mpz_set_ui(g, 135);
	mpz_set_ui(a, 218);
	mpz_set_ui(p, 6128651);
	expMod(r, p, g, a);
	printf("\n");
	mpz_out_str(NULL, 10, r);
	printf("\n");

	mpz_set_ui(g, 135);
	mpz_set_ui(a, 218);
	mpz_set_ui(p, 6128651);
	mpz_set_ui(r, 0);
	mpz_powm(r, g, a, p);
	mpz_out_str(NULL, 10, r);
	printf("\n");*/
}

int main(int argc, char* argv){
    /*
	  mpz_t g, p, u, v, r, a;

    // G initialization
    mpz_inits(g, u, v, r, a, (void *) NULL);
    mpz_set_ui(g, 2);

    // P initialization
    mpz_init_set_str(p, P_HEX_VALUE, 16);
	euclide(r, u, v, g, p);

	mpz_out_str(NULL, 10, u);
	printf(" et ");
	mpz_out_str(NULL, 10, v);
	printf(" et ");
	mpz_out_str(NULL, 10, r);
	*/
	tests_subtils();
    return 0;
}



/*
 * calcule a*u0 + p*v0 = pgcd(a, b)
 * le résultat est stocké dans r0, v0 et u0
 * initialiser r0, v0 et u0 avant l'appel à la fonction
 */
void euclide(mpz_t r0, mpz_t u0, mpz_t v0, mpz_t a, mpz_t p){
	mpz_t r, r1, u, u1, q, v, v1;
	mpz_inits(r, r1, u, u1, q, v, v1, (void *) NULL);
    mpz_set(r0, a);
    mpz_set(r1, p);
    mpz_set_ui(u0, 1);
    mpz_set_ui(u1, 0);

    mpz_set_ui(v0, 0);
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

/*
 * renvoie A ≡ g^a mod p
 * le résultat est stocké dans r
 * initialiser r avant l'appel à la fonction
 */
void expMod(mpz_t r, mpz_t p, mpz_t g, mpz_t a){
	mpz_t quotient, rest, r0, r1, r2, r3;
	mpz_inits(quotient, rest, r0, r1, r2, r3, (void *)NULL);
   	mpz_tdiv_qr_ui(quotient, rest, a, 2);

	if(mpz_sgn(a) == 0){
		mpz_set_ui(r, 1);
	}else if(mpz_cmp_ui(a, 1)==0){
		mpz_mod(r, g, p);
	} else if(mpz_sgn(rest)==0){
		//expmod(g^2 mod p , a/2)
		//g^2
		mpz_mul(r0, g, g);
		//mod p
		mpz_mod(r1, r0, p);
		//expMod(r0, p, g, 2);
		expMod(r, p, r1, quotient);
	} else {
		//expmod((g × puissance(g^2 mod p , (a − 1)/2) )mod p)
		//g^2
		mpz_mul(r0, g, g);
		//mod p
		mpz_mod(r1, r0, p);
		//(a-1) / 2
		mpz_sub_ui(a, a, 1);
		mpz_tdiv_q_ui(quotient, a, 2);

		expMod(r2, p, r1, quotient);

		mpz_mul(r3, r2, g);
		mpz_mod(r, r3, p);
	}
}

/*
KeyGen() est la fonction qui génère les clés de Bob, elle prend en entrée/sortie sans les modifier
p et g, elle tire au hasard un x, la clé secrète de Bob et calcule sa clé publique correspondante
X ≡ g x mod p. Elle renvoie en sortie x et X.
*/
void keyGen(mpz_t x, mpz_t big_x ,mpz_t p, mpz_t g){
	mpz_t boundary;
	gmp_randstate_t state;

	mpz_init(boundary);
	mpz_sub_ui(boundary, p, 2);

	gmp_randinit_default(state);
	//gmp_randseed_ui(state, time(NULL));
	gmp_randseed_ui(state, 123987);
	mpz_urandomm(x, state, boundary);
	mpz_add_ui(x, x, 2);

	expMod(big_x, p, g, x);
}

/*
Encrypt() est la fonction qui produit en sortie le couple chiffré (C ≡ m × y mod p, B ≡
g r mod p) en prenant en entrée la clé publique de Bob K p = (p, g, X) et un message m.
*/
void encrypt(mpz_t c, mpz_t b, mpz_t big_x ,mpz_t p, mpz_t g, mpz_t m){
	mpz_t boundary, r, y;
	gmp_randstate_t state;
	mpz_inits(boundary, r, y, (void *)NULL);

	// tirer r au hasard 2 et p-2
	mpz_sub_ui(boundary, p, 2);

	gmp_randinit_default(state);
	long df = time(NULL);
	//printf("%d", df);
	gmp_randseed_ui(state, df);
	//gmp_randseed_ui(state, 1519673962);
	mpz_urandomm(r, state, boundary);
	mpz_add_ui(r, r, 2);
	printf("\n r : ");
	mpz_out_str(NULL, 10, r);
	printf("\n");

	//y ≡ X r mod p.
	expMod(y, p, big_x, r);

	//C ≡ m × y mod p
	mpz_mul(c, m, y);
	mpz_mod(c, c, p);

	//B ≡ g^r mod p
	expMod(b, p, g, r);
}

/*
Decrypt() est la fonction de déchiffrement qui prend en entrée (C, B) et la clé secrète de Bob
Ks = x et produit en sortie le message m.
*/
void decrypt(mpz_t m, mpz_t c, mpz_t b, mpz_t x, mpz_t p){
	mpz_t d, g, u, v, r, a;
    mpz_inits(d, r, u, v, (void *) NULL);

	// D = B^x mod p
	expMod(d, p, b, x);

	// D^-1 est dans u
	euclide(r, u, v, d, p);

	//m = C × D^−1 mod p.
	mpz_mul(m, c, u);
	mpz_mod(m, m, p);

}
