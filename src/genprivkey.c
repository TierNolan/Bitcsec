/*
 * genprivkey.c
 *
 *  Created on: 2 Jul 2011
 *      Author: 
 */

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include "argmap.h"
#include "genprivkey.h"
#include "hash.h"

int genPrivateKey(argMap map) {

	unsigned char *phrase = getArg("phrase", NULL, map);

	unsigned char hash[SHA256_DIGEST_LENGTH];

	if (phrase != NULL) {
		printf("Generating private key\n\n");
		printf("Pass phrase %s\n\n", phrase);

		genRepeatSHA256(phrase, strlen((signed char*) phrase), hash, 1024*1024);
	} else {
		printf("Generating random private key\n\n");

		if (RAND_bytes(hash, SHA256_DIGEST_LENGTH) == 0) {
			fprintf(stderr, "Error: random number generation failed\n");
			return 0;
		}
	}

	printf("Private key is ");
	printHash(hash, 32);
	printf("\n");

	return 1;

}
