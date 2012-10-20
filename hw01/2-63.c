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
