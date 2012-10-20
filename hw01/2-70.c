// 2.70
/* Return 1 when x can be represented as an n-bit, 2's complement number, 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits (int x, int n) {
    // true if -2^(n-1) <= x <= 2^(n-1) - 1
    int y = !(x >> n);              //  x <= 2^(n-1) - 1
    int z = !((~x) >> n);           // -x <= 2^(n-1)
    int w = !!(n >> sizeof(int));   // n >= 32
    //printf("y: %x\tz: %x\n", y, z);
    return  w || y || z;
}

main () {
    printf("%i\n", fits_bits(0xF0000000, 32));
    printf("%i\n", fits_bits(0xFF, 8));
    printf("%i\n", fits_bits(0x80000001, 8));
    printf("%i\n", fits_bits(0xFFFFFFFF, 8));
}
