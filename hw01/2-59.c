// 2.59
// expression => least significant byte of x, and remaining byte of y
int p2_59 (int x, int y) {
    return ((x & 0xFF) & (y & ~0xFF));
}
