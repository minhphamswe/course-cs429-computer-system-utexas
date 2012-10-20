// 2.60 
// return unsigned value in which byte i of (unsigned) x has been
// replaced by (byte) b
unsigned replace_byte (unsigned x, int i, unsigned char b) {
    unsigned y = x & ~(0xFF << (i << 3));
    unsigned z = b << (i << 3);
    return y | z;
}
