#include <stdio.h>

int src[8000], dst[8000];

/* $begin ncopy */
/*
 * ncopy - copy src to dst, returning number of positive ints
 * contained in src array.
 */
int ncopy(int *src, int *dst, int len)
{
    int count = 0;
    int val;

    while (len > 0) {
	val = *src++;
	*dst++ = val;
	if (val > 0)
	    count++;
	len--;
    }
    return count;
}
/* $end ncopy */

int main()
{
    int i, count;

    for (i=0; i<8000; i++)
	src[i]= i+1;
    count = ncopy(src, dst, 8000);
    printf ("count=%d\n", count);
    return 0;
}


