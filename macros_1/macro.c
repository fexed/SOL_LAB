#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define dimN 16
#define dimM  8

#define CHECK_PTR(M, str) \
	if (M == NULL) { \
		perror("Errore in allocazione"); \
		return -1; \
	}

#define ELEM(M, i, j) M[i+(dimN*j)]

#define PRINTMAT(M, dimN, dimM) \
	int i, j; \
	for (i = 0; i < dimN; i++) { \
		for (j = 0; j < dimM; j++) printf("%ld\t", ELEM(M, i, j)); \
		printf("\n"); \
	} \

int main() {
    long *M = malloc(dimN*dimM*sizeof(long));
    CHECK_PTR(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
	for(size_t j=0;j<dimM;++j)			
	    ELEM(M,i,j) = i+j;    
    
    PRINTMAT(M, dimN, dimM);
    free(M);
    return 0;
}