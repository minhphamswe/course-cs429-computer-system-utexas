// 2.64
// return 1 when any odd bit of x equals 1; 0 otherwise.
// assume w=32
int any_odd_one (unsigned x) {
    /* fill all even bits with 0s */
    int mask = 0x55555555;
    int filled = x & mask;
    
    /* check that not all bits of filled is 0 */
    printf("x: %x\tfilled: %x\n", x, filled);
    return !!(filled);
}

main () {
    printf("%i\n%i\n", any_odd_one(0x80000000), any_odd_one(0x40000000));
}
