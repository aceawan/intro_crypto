#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv){
	FILE* result_file = fopen("test.txt", "w+");

	if(result_file == NULL){
		printf("Erreur d'ouverture de fichier\n");
		return -2;
	}

	test_euclide(result_file);
	test_expMod(result_file);
	test_encryption(result_file);
	test_homomorphie(result_file);

	fclose(result_file);
    return 0;
}

void test_expMod(FILE* result_file){
	int i;
	int result = 0;

	fprintf(result_file, "\nTest de l'exponentiation modulaire : \n\n");

	for(i=2; i<10000; i++){
		mpz_t r, g, p, a;
		mpz_t r2;

		mpz_inits(r, r2, g, p, a,  (void *) NULL);
		mpz_init_set_str(p, P_HEX_VALUE, 16);

		mpz_set_ui(g, i);
		mpz_set_ui(a, 2);

		expMod(r, p, g, a);
		mpz_powm(r2, g, a, p);

		if(i < 7){
			char* g_str = mpz_get_str(NULL, 10, g);
			char* p_str = mpz_get_str(NULL, 10, p);
			char* a_str = mpz_get_str(NULL, 10, a);
			char* r_str = mpz_get_str(NULL, 10, r);

			fprintf(result_file, "%s^%s mod %s = %s\n", g_str, a_str, p_str, r_str);
		}

		if(mpz_cmp(r, r2)!=0){
			printf("\nErreur:\n");
			mpz_out_str(NULL, 10, r);
			printf("\n et  \n");
			mpz_out_str(NULL, 10, r2);
			result = -1;
		}

		mpz_clears(r, r2, g, p, a,  (void *) NULL);
	}

	if(result == 0){
		printf("\nTest expMod corrects\n");
	}
	else{
		printf("\nLe test d'exponentiation modulaire a réussi.\n");
	}
}

void test_euclide(FILE* result_file){
	int i;
	int result = 0;

	fprintf(result_file, "Tests d'Euclide : \n\n");
	for(i=2; i<10002; i++){
		mpz_t r, u, v, g, p;
		mpz_t r2, u2, v2;
		mpz_inits(r, u, v, g, p,  (void *) NULL);
		mpz_set_ui(g, i);
		mpz_init_set_str(p, P_HEX_VALUE, 16);

		euclide(r, u, v, g, p);

		mpz_inits(r2, u2, v2,  (void *) NULL);
		mpz_gcdext(r2, u2, v2, g, p);

		if(i < 7){
			char* u_str = mpz_get_str(NULL, 10, u);
			char* v_str = mpz_get_str(NULL, 10, v);
			char* r_str = mpz_get_str(NULL, 10, r);
			char* g_str = mpz_get_str(NULL, 10, g);
			char* p_str = mpz_get_str(NULL, 10, p);

			fprintf(result_file, "%s * %s + %s * %s = %s\n", u_str, g_str, v_str, p_str, r_str);
		}


		if(mpz_cmp_ui(r, 1)!=0){
			printf("\nErreur:\n");
			mpz_out_str(NULL, 10, u);
			printf(" et ");
			mpz_out_str(NULL, 10, v);
			printf(" et ");
			mpz_out_str(NULL, 10, r);
			result = -1;
		}

		if(mpz_cmp(u, u2)!=0 || mpz_cmp(u, u2)!=0){
			printf("\nErreur:\n");
			mpz_out_str(NULL, 10, u);
			printf(" | ");
			mpz_out_str(NULL, 10, u2);
			printf("\n et \n");
			mpz_out_str(NULL, 10, v);
			printf(" | ");
			mpz_out_str(NULL, 10, v2);
			printf("\n et \n");
			mpz_out_str(NULL, 10, r);
			printf(" | ");
			mpz_out_str(NULL, 10, r);
			printf("\n");
			result = -1;
		}

		mpz_clears(r2, u2, v2,  (void *) NULL);
		mpz_clears(r, u, v, g, p,  (void *) NULL);
	}
	if(result == 0){
		printf("\nTest Euclide corrects\n");
	}
}

void test_encryption(FILE* result_file){
	int i;
	int result = 0;
	mpz_t old_x;
	mpz_inits(old_x, (void*) NULL);

	fprintf(result_file, "\nTests de chiffrement :\n\n");

	for(i=2; i<102; i++){
		mpz_t m, c, d, p, g, x, big_x, b;
		mpz_inits(m, c, d, p, g, x, big_x, b, (void*) NULL); 
		mpz_set_ui(m, i);
		mpz_init_set_str(p, P_HEX_VALUE, 16);
		mpz_set_ui(g, 2);

		keyGen(x, big_x, p, g);

		if(i > 2){
			if(mpz_cmp(old_x, x) == 0){
				result = -2;
			}
		}

		mpz_set(old_x, x);

		encrypt(c, b, big_x, p, g, m);
		decrypt(d, c, b, x, p);

		if(i < 7){
			char* message = mpz_get_str(NULL, 10, m);
			char* chiffre = mpz_get_str(NULL, 10, c);
			char* dechiffre = mpz_get_str(NULL, 10, d);
			fprintf(result_file, "message = %s, chiffré = %s, déchiffré = %s\n", message, chiffre, dechiffre);
		}

		if(mpz_cmp(m, d) != 0){
			result = -1;
		}
	}

	if(result == 0){
		printf("\nTests de chiffrement-déchiffrement corrects\n");
	} else if (result == -2){
		printf("\nNombre aléatoires identiques\n");
	}
	else {
		printf("\nErreur de chiffrement déchiffrement\n");
	}
}

void test_homomorphie(FILE* result_file){
	mpz_t p, g, x, big_x, m1, m2, b1, b2, c1, c2, d, product_m, product_c, product_b;
	mpz_inits(p, g, x, big_x, m1, m2, b1, b2, c1, c2, d, product_m, product_c, product_b, (void *)NULL);

	// Initialize the values
	mpz_init_set_str(p, P_HEX_VALUE, 16);
	mpz_set_ui(g, 2);
	mpz_set_ui(m1, randombytes_uniform(1000000));
	mpz_set_ui(m2, randombytes_uniform(1000000));
	mpz_mul(product_m, m1, m2);

	// Generate the keys
	keyGen(x, big_x, p, g);

	// Encryption of m1 and m2
	encrypt(c1, b1, big_x, p, g, m1);
	encrypt(c2, b2, big_x, p, g, m2);
	mpz_mul(product_c, c1, c2);
	mpz_mul(product_b, b1, b2);

	// Decryption of m1 x m2
	decrypt(d, product_c, product_b, x, p);

	mpz_mod(d, d, p);

	fprintf(result_file, "\nTest d'homomorphie : \n\n");

	char* message1 = mpz_get_str(NULL, 10, m1);
	char* message2 = mpz_get_str(NULL, 10, m2);
	char* produitm1m2 = mpz_get_str(NULL, 10, product_m);
	char* produitdechiffres = mpz_get_str(NULL, 10, d);

	fprintf(result_file, "m1 = %s, m2 = %s, m1xm2 mod p = %s, déchiffré du produit des chiffrés de m1 et m2 = %s", message1, message2, produitm1m2, produitdechiffres);

	if(mpz_cmp(d, product_m) != 0){
		printf("ERREUR HOMOMORPHIE\n");
	}
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
	mpz_clears(r, r1, u, u1, q, v, v1, (void *) NULL);
}

/*
 * renvoie A ≡ g^a mod p
 * le résultat est stocké dans r
 * initialiser r avant l'appel à la fonction
 */
void expMod(mpz_t r, mpz_t p, mpz_t g, mpz_t a){
	mpz_t quotient, rest, g_pow_2, r1, r2, r3;
	mpz_inits(quotient, rest, g_pow_2, r1, r2, r3, (void *)NULL);
   	//mpz_tdiv_qr_ui(quotient, rest, a, 2);
	if(mpz_cmp_ui(a, 1)==0){
		mpz_mod(r, g, p);
	} else{
		mpz_mod_ui(rest, a, 2);
		if(mpz_cmp_ui(rest, 0)==0){
			//expmod(r, p, g^2, a/2)
			//a/2
			mpz_tdiv_q_ui(quotient, a, 2);
			//g^2
			mpz_mul(g_pow_2, g, g);
			//expMod(r0, p, g, 2);
			expMod(r, p, g_pow_2, quotient);
			//mod p
			mpz_mod(r, r, p);
		} else { // a impair
			if(mpz_cmp_ui(a, 2)>0){
				//g*expmod(r, p, g^2, (a − 1)/2) mod p ) mod p
				//g^2
				mpz_mul(g_pow_2, g, g);
				mpz_mod(g_pow_2, g_pow_2, p);
				//(a-1) / 2
				mpz_sub_ui(quotient, a, 1);
				mpz_tdiv_q_ui(quotient, a, 2);

				expMod(r, p, g_pow_2, quotient);
				mpz_mod(r, r, p);

				mpz_mul(r, r, g);
				mpz_mod(r, r, p);
			}
		}
	}
		mpz_clears(quotient, rest, g_pow_2, r1, r2, r3, (void *)NULL);
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
	mpz_sub_ui(boundary, p, 1);

	gmp_randinit_default(state);
	int random_seed = randombytes_uniform(10000000);
	gmp_randseed_ui(state, random_seed);
	//gmp_randseed_ui(state, 123987);
	mpz_add_ui(x, x, 2);
	mpz_urandomm(x, state, boundary);

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
	//long df = time(NULL);
	//printf("%d", df);
	//gmp_randseed_ui(state, df);
	gmp_randseed_ui(state, time(NULL)*5);
	mpz_urandomm(r, state, boundary);
	mpz_add_ui(r, r, 2);

	//y ≡ X r mod p.
	expMod(y, p, big_x, r);

	//mpz_invert(test, y, p);

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
	mpz_t d, g, u, v, r, a, test, t;
    mpz_inits(d, r, u, v, test,t,  (void *) NULL);

	// D = B^x mod p
	expMod(d, p, b, x);

	// D^-1 est dans u
	euclide(r, u, v, d, p);

	//m = C × D^−1 mod p.
	mpz_mul(m, c, u);


	//mpz_mul(m, c, u);
	mpz_mod(m, m, p);

	mpz_clears(d, r, u, v, test,t,  (void *) NULL);
}
