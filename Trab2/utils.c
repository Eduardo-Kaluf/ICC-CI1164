// EDUARDO KALUF - GRR 20241770

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "edo.h"


rtime_t timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (rtime_t) tp.tv_sec*1.0e3 + (rtime_t) tp.tv_nsec*1.0e-6 );
}

string_t markerName(string_t baseName, int n)
{
    string_t mark = (string_t) malloc( (strlen(baseName)+1) + numDigits(n) + 1 );

  sprintf(mark, "%s_%u", baseName,n);

  // printf("*** %s\n", mark);

  return mark;

}

void print_vector(real_t *v, int n) {
    for (int i = 0; i < n; i++)
        printf(FORMAT, v[i]);
    printf("\n");
}
