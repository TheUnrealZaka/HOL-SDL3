#include <stdio.h>
#include "memory/measure.h"
#ifndef N
#define N 256  /* Dimensión por defecto */
#endif

static float A[N][N], B[N][N], C[N][N];

/* Execute the call f() and measure its execution time in useconds */
static double measure( void (*f)(void) )
{
    return measure_full((int(*)(int,int))f, 0xDEAD, 0xDEAD, 1, 0.01, 1); // Single execution
}

static void init_data(); // Declaració static
static void code(); // Declaració static

int mm_ijk() { // Aquesta NO és static
  double t;
  int i, j;

  // Inicializacion de las matrices A, B y C
  init_data();

  // CODIGO A EVALUAR: forma ijk del producto de dos matrices de tamaño NxN
  t = measure(code);

  if (N > 6) {
    printf("FORMA ijk (%d), Milisegundos = %9f \n\n", N, t/1000.0);
  }
  if (N <= 6) {
    printf("\nFORMA ijk \n\n");
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++)
        printf("%10f ", C[i][j]);
      printf ("\n");
    }
  }

#ifdef _WIN32
  printf("Press return to continue\n");
  char c;
  read(0, &c, 1);
#endif
  return 0;
}

static void init_data()
{
  float x;
  int i, j;
  x = 0.001;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++) {
      A[i][j] = x * i + x * j;
      B[i][j] = x * i + x * j;
      C[i][j] = 0.0;
    }
}

static void code()
{
  int i, j, k;
  for (i=0; i<N; i++) 
    for (j=0; j<N; j++)
      for (k=0; k<N; k++)
        C[i][j] += A[i][k] * B[k][j];
}
