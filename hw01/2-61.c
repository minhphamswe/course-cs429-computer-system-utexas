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
