#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libstdc/include/libstdc/config.h"
#include "../libstdc/include/malloc.h"
#include "../libstdc/include/string.h"

#define ARRAYLEN(A) sizeof(A) / sizeof(*A)

char *__cxa_demangle_gnu3(const char *);

#include "demangle_cases.inc"

#define BUFFER_SIZE 4096

int main()
{
    char buffer[BUFFER_SIZE];
    __OSDEV_STD_SYMBOL(libstdc_allocator_initialize(buffer, BUFFER_SIZE));

	for (int i = 0; i < ARRAYLEN(demangle_cases); ++i) {
		const char *input = demangle_cases[i][0];
		const char *want = demangle_cases[i][1];
		char *res = __cxa_demangle_gnu3(input);
		if (!res) {
			fprintf(stderr, "\n");
			fprintf(stderr, "DEMANGLE TEST FAILED:\n");
			fprintf(stderr, "\tinput: %s\n", input);
			fprintf(stderr, "\twant:  %s\n", want);
			fprintf(stderr, "\tgot:   null result\n");
			fprintf(stderr, "\n");
			exit(10);
		}
		if (__OSDEV_STD_SYMBOL(strcmp)(res, want)) {
			fprintf(stderr, "\n");
			fprintf(stderr, "DEMANGLE TEST FAILED:\n");
			fprintf(stderr, "\tinput: %s\n", input);
			fprintf(stderr, "\twant:  %s\n", want);
			fprintf(stderr, "\tgot:   %s\n", res);
			fprintf(stderr, "\n");
			exit(20);
		}
        __OSDEV_STD_SYMBOL(free)(res);
	}
}