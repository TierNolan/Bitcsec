/*
 * doublesha.h
 *
 *  Created on: 2 Jul 2011
 *      Author: 
 */

#ifndef DOUBLESHA_H_
#define DOUBLESHA_H_

#include <stdio.h>

unsigned char *genRIPEMD160(unsigned char *message, int length,
		unsigned char *hash);
unsigned char *genSHA256RIPEMD160(unsigned char *message, int length,
		unsigned char *hash);

unsigned char *genRepeatSHA256(unsigned char *message, int length,
		unsigned char *hash, int count);
unsigned char *genDoubleSHA256(unsigned char *message, int length,
		unsigned char *hash);

unsigned char *genSHA256(unsigned char *message, int length,
		unsigned char *hash);

void fprintfHash(FILE *fp, unsigned char* hash, int length);
void printHash(unsigned char* hash, int length);

#endif /* DOUBLESHA_H_ */
