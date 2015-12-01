CC = gcc
CFLAGS = -std=gnu11 -Wall

all: shared_library_test1 shared_library_test2 libslt.so.1

shared_library_test1: shared_library_test1.o libslt.so.1
	$(CC) $(CFLAGS) shared_library_test1.o libslt.so.1 -o shared_library_test1

shared_library_test2: shared_library_test2.o libslt.so.1
	$(CC) $(CFLAGS) shared_library_test2.o libslt.so.1 -o shared_library_test2 -lm

libslt.so.1: libslt.so.1.0.0
	ln -s libslt.so.1.0.0 libslt.so.1

libslt.so.1.0.0: shared_library_test_lib.o
	$(CC) -shared -Wl,-soname,libslt.so.1 shared_library_test_lib.o -o libslt.so.1.0.0

shared_library_test_lib.o: shared_library_test_lib.c
	$(CC) $(CFLAGS) -fPIC -c shared_library_test_lib.c -o shared_library_test_lib.o

shared_library_test1.o: shared_library_test1.c
	$(CC) $(CFLAGS) -c shared_library_test1.c -o shared_library_test1.o

shared_library_test2.o: shared_library_test2.c
	$(CC) $(CFLAGS) -c shared_library_test2.c -o shared_library_test2.o

clean:
	rm -f *.o *.so.* shared_library_test1 shared_library_test2
