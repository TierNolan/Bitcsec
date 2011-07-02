CC = gcc
OBJ = obj
SRC = src
RUN = run
OPENSSL = ./openssl/openssl-1.0.0d
PATHS = -L$(OPENSSL) -lssl -lcrypto -I$(OPENSSL)/include

MAIN = bitcsec

OBJECTS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(wildcard $(SRC)/*.c))

$(RUN)/$(MAIN): $(OBJECTS) $(OBJECTS_BITCOIN)
	$(CC) $(OBJECTS) $(OBJECTS_BITCOIN) $(PATHS) -o $(RUN)/$(MAIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(PATHS) -I$(OPENSSL)/include -c $< -o $@

clean:
	\rm run/* obj/* 
