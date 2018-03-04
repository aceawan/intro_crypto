#ifndef MAIN_H
#define MAIN_H

#include <gmp.h>
#include <sodium.h>

#define P_HEX_VALUE "FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 49286651 ECE65381 FFFFFFFF FFFFFFFF"

void euclide(mpz_t r0, mpz_t u0, mpz_t v0, mpz_t a, mpz_t p);
void expMod(mpz_t r, mpz_t p, mpz_t g, mpz_t a);
void keyGen(mpz_t x, mpz_t big_x ,mpz_t p, mpz_t g);
void encrypt(mpz_t c, mpz_t b, mpz_t big_x ,mpz_t p, mpz_t g, mpz_t m);
void decrypt(mpz_t m, mpz_t c, mpz_t b, mpz_t x, mpz_t p);
void test_euclide();
void test_expMod();
void test_encryption();
void test_homomorphie();
#endif
