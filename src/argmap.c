/*
 * argmap.c
 *
 *  Created on: 2 Jul 2011
 *      Author: 
 */

#include <stdlib.h>
#include <string.h>

#include "argmap.h"

int scanArgs(int argc, char **argv, argMap *map) {

	int a;
	for (a = 1; a < argc; a++) {
		char *arg = argv[a];
		if (*arg == '-') {
			valueArray *array = getValueArray(arg + 1, map, 1);
			if (array == NULL) {
				fprintf(stderr, "Error: Unable to create key %s\n", arg + 1);
				return 0;
			}

			char *value;
			if (a < argc - 1) {
				if (*argv[a + 1] == '-') {
					value = NULL;
				} else {
					value = argv[a + 1];
				}
			} else {
				value = NULL;
			}
			if (addValue(array, value) == 0) {
				fprintf(stderr, "Error: Unable to add value to key %s\n",
						argv[a + 1] + 1);
				return 0;
			}
			if (value != NULL) {
				a++;
			}
		} else {
			fprintf(stderr, "Error: unknown parameter %s\n", argv[a]);
		}
	}

	return 1;

}

int initMap(argMap *map) {
	map->key.num = 0;
	map->key.values = NULL;

	map->values = NULL;

	return 1;
}

int addValue(valueArray *valueArray, char *value) {

	valueArray->values = realloc(valueArray->values,
			(sizeof *(valueArray->values)) * (valueArray->num + 1));

	if (valueArray->values == NULL) {
		return 0;
	}

	if (value != NULL) {
		valueArray->values[valueArray->num] = value;

		valueArray->num++;
	}

	return 1;
}

valueArray *getValueArray(char *key, argMap *map, int create) {

	int a;
	for (a = 0; a < map->key.num; a++) {
		if (strncmp(key, map->key.values[a], strlen(key)) == 0) {
			return map->values + a;
		}
	}

	if(!create) {
		return NULL;
	}

	if (addValue(&(map->key), key) == 0) {
		return NULL;
	}

	map->values = realloc(map->values, sizeof(*map->values));

	if (map->values == NULL) {
		return NULL;
	}

	valueArray *newArray = &(map->values[map->key.num - 1]);

	initValueArray(newArray);

	return newArray;

}

valueArray *createValueArray() {

	valueArray *newArray = malloc((sizeof *newArray));

	if (newArray == NULL) {
		return NULL;
	}

	if (initValueArray(newArray) == 0) {
		return NULL;
	}

	return newArray;
}

int initValueArray(valueArray *array) {
	array->num = 0;
	array->values = NULL;
	return 1;
}

void printArgs(argMap map) {
	int a;
	for (a = 0; a < map.key.num; a++) {
		printf("Key:    %s\n", map.key.values[a]);
		printf("Values: ");
		int b;
		for (b = 0; b < map.values[a].num; b++) {
			if (b > 0) {
				printf(", ");
			}
			printf("%s", map.values[a].values[b]);
		}
		printf("\n");
	}
}

int validate(valueArray params, argMap map) {
	int a;
	for (a = 0; a < map.key.num; a++) {
		int match = 0;
		int b;
		for (b = 0; b < params.num; b++) {
			if (strncmp(params.values[b], map.key.values[a],
					strlen(params.values[b])) == 0) {
				match = 1;
				break;
			}
		}
		if (match == 0) {
			fprintf(stderr, "Error: parameter %s is not a known parameter\n",
					map.key.values[a]);
			return 0;
		}
	}
	return 1;
}

char *getArg(char *key, char *def, argMap map) {

	valueArray *valueArray = getValueArray(key, &map, 0);
	if (valueArray == NULL) {
		return NULL;
	} else if (valueArray->num == 0) {
		return "true";
	} else {
		return valueArray->values[0];
	}

}

valueArray strArrToValueArray(char *arr[]) {

	int len = 0;
	while (arr[len] != NULL) {
		len++;
	}

	valueArray newArray;
	initValueArray(&newArray);

	newArray.num = len;
	newArray.values = arr;

	return newArray;

}
