// 2.68
/* Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask (int n) {
    int n_is_32 = !(n ^ 32);            // 1 if n == 32, 0 otherwise
    int mask = n_is_32 << 31 >> 31;     // 0xFFFFFFFF if n == 32, 0 otherwise
    return (mask & 0xFFFFFFFF) | (~mask & ~(~0 << n));
}

main () {
    printf("%x\n%x\n%x\n", lower_one_mask(6), lower_one_mask(17), lower_one_mask(32));
}
