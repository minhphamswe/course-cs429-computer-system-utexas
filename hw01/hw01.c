#include <stdio.h>

//~ 2.57
//~ show_short, show_long, show_double =>
//~ byte representation of C objects of types
//~ short int, long int, double
typedef unsigned char *byte_pointer

void show_bytes (byte_pointer start, int len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n")
}

void show_short (short x) {
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long (long x) {
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double (double x) {
    show_bytes((byte_pointer) &x, sizeof(double));
}

// 2.59
// expression => least significant byte of x, and remaining byte of y
int p2_59 (int x, int y) {
    return ((x & 0xFF) & (y & ~0xFF));
}

// 2.60 
// return unsigned value in which byte i of (unsigned) x has been
// replaced by (byte) b
unsigned replace_byte (unsigned x, int i, unsigned char b) {
    unsigned y = x & ~(0xFF << (i << 3));
    unsigned z = b << (i << 3);
    return y | z;
}
// 2.61
// A: any bit of x == 1
int p2_61a (int x) {
    /* check that not all bits in x is 0 (in which case x == 0) */
    return !!(x);
}
// B: any bit of x == 0
int p2_61b (int x) {
    return !!(~x);
}
// C: any bit in the least significant byte of x equals 1
int p2_61c (int x) {
    /* zero all but LSB, and check that the result is not 0 */
    return !!(x & 0xFF);
}
// D: any bit in the most significant byte of x equals 0
int p2_61d (int x) {
    /* fill all non-MSB bits with 1s */
    int msb = (x & 0xFF) | 0x00FFFFFF;
    /* check if there's any 0 in the result */
    return !!(~msb);
}

// 2.63
// arithmetic shift to logical shift
unsigned srl (unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned sxra = (int) x >> k;
    
    /* student code begins */
    unsigned mask = ~0 >> k;
    return sxra & mask;
    /* student code ends */
}

// logical shift to arithmetic shift
int sra (int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    
    /* student code begins */
    int sign = !!(x >> 31);         // == 1 if x < 0; 0 otherwise
    int mask = sign << 31 >> k;     // off-by-one, but is of no consequence
    return xsrl | mask;
    /* student code ends */
}

// 2.64
// return 1 when any odd bit of x equals 1; 0 otherwise.
// assume w=32
int any_odd_one (unsigned x) {
    /* fill all even bits with 0s */
    int mask = 0x55555555;
    int filled = x | mask;
    
    /* check that not all bits of filled is 0 */
    return !!(filled);
}

// 2.66
/* Generate mask indicating leftmost 1 in x. Assume w=32.
 * For example 0xFF00 -> 0x8000, and 0x6600 -> 0x4000
 * If x = 0, return 0 
 */
int leftmost_one (unsigned x) {
}

// 2.67
// returns 1 when run on a machine for which an int is 32 bits, 0 otherwise
int int_size_is_32 () {
    /* set msb of 32-bit machines */
    int set_msb = 1 << 31;
    
    /* shift past msb of 32-bit word */
    int beyond_msb = 1 << 32;
    
    /* set_msb is non-zero when word size >= 32
     * beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

// 2.68
/* Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x2F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask (int n) {
}

// 2.69
/* Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */
unsigned rotate_left (unsigned x, int n) {
}

// 2.70
/* Return 1 when x can be represented as an n-bit, 2's complement number, 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits (int x, int n) {
}

int main(int argc, char** argv) {
    int x = 0x89ABCDEF;
    int y = 0x76543210;
    short s = 0xABCD;
    long l = 0x12345678L;
    double d = 0.55D;
    
    printf("2.57: \n");
    show_short(s);
    show_long(l);
    show_double(d);
    
    printf("2.59:\n");
    printf("expression => least significant byte of x, and remaining byte of y\n");
    printf("expect: 0x765432EF\nget: %x\n", p2_59(x, y));
    printf("2.60: \n%X\n%X\n", replace_byte(0x12345678, 2, 0xAB), replace_byte(0x12345678, 0, 0xAB));
    return 0;
}
