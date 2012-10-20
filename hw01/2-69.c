// 2.69
/* Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */
unsigned rotate_left (unsigned x, int n) {
    return (x << n) | (x >> ((sizeof(int) << 3) - n));
}

main () {
    printf("%x\n%x\n", rotate_left(0x12345678, 4), rotate_left(0x12345678, 20));
}
