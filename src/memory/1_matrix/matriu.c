#include <stdio.h>
#include "memory/measure.h"
#include <stdlib.h>


#define N 64
#define ROWS N
#define COLS N

/* Data matrix */
static char M[ROWS][COLS];

/* Execute the call f() and measure its execution time in useconds */
static double measure( void (*f)(void) )
{
	return measure_full((int(*)(int,int))f, 0xDEAD, 0xDEAD, 3, 0.01, 10); // 1% error
}

/* init_data - initializes the array */
static void init_data()
{
	int i, j;
	for(i=0; i<ROWS; i++) {
		for(j=0; j<COLS; j++) {
			M[i][j] = i+j*10;
		}
	}
}

/* Traverse matrix 'M' by rows */
static void matrix_rows()
{
	int i, j;
	for(i=0; i<ROWS; i++) {
		for(j=0; j<COLS; j++) {
			M[i][j] = i+j;
		}
	}
}

/* Traverse matrix 'M' by columns */
static void matrix_cols()
{
	int i, j;
	for(j=0; j<COLS; j++) {
		for(i=0; i<ROWS; i++) {
			M[i][j] = i+j;
		}
	}
}

int matriu() // Aquesta funció NO és static perquè és cridada des de main
{
    printf(" Matrix of %d x %d elements \n", ROWS, COLS);
    printf("    Size = %8ld bytes / %8ldKiBs / %8ldMiBs\n", sizeof(M), sizeof(M)/1024, sizeof(M)/(1024*1024));
    printf(" rowsize = %8ld bytes / %8ldKiBs / %8ldMiBs\n", COLS*sizeof(M[0][0]), COLS*sizeof(M[0][0])/1024, COLS*sizeof(M[0][0])/(1024*1024));

    init_data();

    //Initial traversal to warmup the memory...
    printf(" * Time to initialize : %f useconds\n", measure(matrix_rows));

    printf(" Traverse using ROWS...\n");
    printf(" * Time (1)           : %f useconds\n", measure(matrix_rows));
    printf(" * Time (2)           : %f useconds\n", measure(matrix_rows));
    printf(" * Time (3)           : %f useconds\n", measure(matrix_rows));
    printf(" Traverse using COLUMNS...\n");
    printf(" * Time (1)           : %f useconds\n", measure(matrix_cols));
    printf(" * Time (2)           : %f useconds\n", measure(matrix_cols));
    printf(" * Time (3)           : %f useconds\n", measure(matrix_cols));

#ifdef _WIN32
    printf("Press return to continue\n");
    char c;
    read(0, &c, 1);
#endif
    return 0;
}
