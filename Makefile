CC=gcc
CFLAGS=-c -Wall -Iinclude/mbedtls/
LDFLAGS=
SOURCES=library/aes.c library/cipher.c library/cipher_wrap.c library/gcm.c library/main.c library/utils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o out

