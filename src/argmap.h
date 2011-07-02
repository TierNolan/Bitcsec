/*
 * argmap.h
 *
 *  Created on: 2 Jul 2011
 *      Author: 
 */

#ifndef ARGMAP_H_
#define ARGMAP_H_

#include <stdio.h>

typedef struct varr {
	int num;
	char **values;
} valueArray;

typedef struct amap {
	valueArray key;
	valueArray *values;
} argMap;

int scanArgs(int argc, char **argv, argMap *map);
int initMap(argMap *map);
int addValue(valueArray *valueArray, char *value);
int initValueArray(valueArray *array);
valueArray *createValueArray();
valueArray *getValueArray(char *key, argMap *map, int create);
void printArgs(argMap map);
int validate(valueArray params, argMap map);
char *getArg(char *key, char *def, argMap map);
valueArray strArrToValueArray(char *arr[]);

#endif /* ARGMAP_H_ */
