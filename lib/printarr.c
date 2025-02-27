#include <stdio.h>
#include <stdint.h>

int64_t printarr(int64_t* a, int64_t n) {
	for (int i = 0; i < n; i++) printf("%ld\n", a[i]);
	return 0;
}