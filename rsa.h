#ifndef __RSA_H__
#define __RSA_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#include "bignum.h"

#define PRIME_DIGIT 50

typedef struct{
	BigInt modulus;
	BigInt public_exp;
} publicKey;

typedef struct{
	BigInt modulus;
	BigInt public_exp;
	BigInt private_exp;
	BigInt prime_p;
	BigInt prime_q;
} privateKey;



//密钥生成函数 
void generate_keys(publicKey* pub_key, privateKey* pri_key);
//加密函数 
BigInt* encrypt(char* cipher, char* message, int length, publicKey kpub);
//解密函数 
BigInt* decrypt(char* message ,char *cipher, int length, privateKey kpri);

BigInt generatePrime();
BigInt get_gcd(BigInt num1, BigInt num2); 
#endif
