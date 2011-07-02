/*
 * doublesha256.c
 *
 *  Created on: 2 Jul 2011
 *      Author: 
 */

#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

unsigned char *genSHA256(unsigned char *message, int length,
		unsigned char *hash) {

	SHA256_CTX ctx;

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, message, length);
	SHA256_Final(hash, &ctx);

	return hash;

}

unsigned char *genRIPEMD160(unsigned char *message, int length,
		unsigned char *hash) {

	RIPEMD160_CTX ctx;

	RIPEMD160_Init(&ctx);
	RIPEMD160_Update(&ctx, message, length);
	RIPEMD160_Final(hash, &ctx);

	return hash;

}

unsigned char *genSHA256RIPEMD160(unsigned char *message, int length,
		unsigned char *hash) {

	genSHA256(message, length, hash);
	genRIPEMD160(hash, SHA256_DIGEST_LENGTH, hash);

	return hash;

}

unsigned char *genDoubleSHA256(unsigned char *message, int length,
		unsigned char *hash) {

	genSHA256(message, length, hash);
	genSHA256(hash, SHA256_DIGEST_LENGTH, hash);

	return hash;

}

unsigned char *genRepeatSHA256(unsigned char *message, int length,
		unsigned char *hash, int count) {

	genSHA256(message, length, hash);
	int x;
	count--;
	for(x=0;x<count;x++) {
		genSHA256(hash, SHA256_DIGEST_LENGTH, hash);
	}

	return hash;

}

void printHash(unsigned char* hash, int length) {
	fprintHash(stdout, hash, length);
}

void fprintHash(FILE *fp, unsigned char* hash, int length) {
	int a;
	for (a = 0; a < length; a++) {
		fprintf(fp, "%02x", hash[a]);
	}
}
