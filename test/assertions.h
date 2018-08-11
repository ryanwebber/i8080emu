#ifndef ASSERT_H
#define ASSERT_H

void _assert_uint_eq(unsigned int a, unsigned int b, const char *file, int line) {
	fprintf(stderr, "\nAssertion failed: Expected [%u] but got [%u] (%s:%i)\n\n", a, b, file, line);
}
#define assert_uint_eq(a,b) if(a != b){ _assert_uint_eq(a,b,__FILE__, __LINE__); return 1; }

#endif
