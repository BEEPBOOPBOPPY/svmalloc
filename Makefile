svmalloctest: svmalloctest.c
	gcc -c -Wall -Werror -fpic svmalloc.c -Wno-deprecated-declarations
	gcc -shared -o libsvmalloc.so svmalloc.o
	gcc -L. -Wall -o svmalloctest svmalloctest.c -lsvmalloc

clean:
	rm libsvmalloc.so
	rm svmalloctest

all: clean svmalloctest

