#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

#include "bitcsec.h"
#include "argmap.h"
#include "genprivkey.h"

char *params[] = { "phrase", "genprivkey", "o", "pubkey", "sendaddr",
		"coinhash", "amount", "address", NULL };

int main(int argc, char **argv) {

	argMap map;

	OpenSSL_add_all_digests();

	if (initMap(&map) && scanArgs(argc, argv, &map)
			&& validate(strArrToValueArray(params), map)) {

		if (getArg("genprivkey", NULL, map) != NULL) {
			genPrivateKey(map);
		}

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;

}

