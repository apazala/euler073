#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 12000

void fillprimes(int upperBound);

int primefactor[LIMIT + 1];
int mobius[LIMIT + 1];
int mertens[LIMIT + 1];

void init() {
	mobius[1] = 1;
	fillprimes(LIMIT);
	mertens[1] = 1;
	int p, mob;
	for (int i = 2; i <= LIMIT; i++) {
		p = primefactor[i];
		if (!p) {
			mob = -1;
		}
		else {
			int ndiv = i / p;
			if (ndiv%p == 0) {
				mob = 0;
			}
			else {
				mob = -mobius[ndiv];
			}
		}
		mobius[i] = mob;
		mertens[i] = mertens[i-1] +	mob;
	}
}

int64_t fareyindex(int k, int n) {
	int64_t t = 0;

	for (int j = 2; j <= n; j++) {
		t += mertens[n / j] * (j / k);
	}

	return t;
}

int64_t solve(int a, int d) {

	int64_t t1 = fareyindex(a+1, d);
	int64_t t2 = fareyindex(a, d);

	return t2-t1-1;
}

int main()
{
	init();

	int a=2, d = 12000;
	printf("%" PRId64 "\n", solve(a, d));
    return 0;
}


void fillprimes(int upperBound) {
	int i, j;
	
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (!primefactor[i]) {
			for (j = i*i; j <= upperBound; j += i) {
				primefactor[j] = i;
			}
		}
	}
	
}