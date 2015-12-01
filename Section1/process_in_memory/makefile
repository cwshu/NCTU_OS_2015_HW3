CC = gcc
CFLAGS = -std=gnu11 -Wall

all: process_in_memory libpim.so.1

process_in_memory: process_in_memory.o libpim.so.1.0.0
	$(CC) $(CFLAGS) process_in_memory.o libpim.so.1.0.0 -o process_in_memory

libpim.so.1: libpim.so.1.0.0
	ln -s libpim.so.1.0.0 libpim.so.1

libpim.so.1.0.0: process_in_memory_lib.o
	$(CC) -shared -Wl,-soname,libpim.so.1 process_in_memory_lib.o -o libpim.so.1.0.0

process_in_memory_lib.o: process_in_memory_lib.c
	$(CC) $(CFLAGS) -fPIC -c process_in_memory_lib.c -o process_in_memory_lib.o

process_in_memory.o: process_in_memory.c
	$(CC) $(CFLAGS) -c process_in_memory.c -o process_in_memory.o

clean:
	rm -f *.o *.so.* process_in_memory
