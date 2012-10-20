// 2.67
// returns 1 when run on a machine for which an int is 32 bits, 0 otherwise

//~ int bad_int_size_is_32 () {
    //~ /* set msb of 32-bit machines */
    //~ int set_msb = 1 << 31;
    //~ 
    //~ /* shift past msb of 32-bit word */
    //~ int beyond_msb = 1 << 32;
    //~ 
    //~ /* set_msb is non-zero when word size >= 32
     //~ * beyond_msb is zero when word size <= 32 */
    //~ return set_msb && !beyond_msb;
//~ }

// A. The behaviour of left-shift by the size of the type (here int) is 
// undefined in the standard.

// B
int int_size_is_32_mod_1 () {
    /* set msb of 32-bit machines */
    int set_msb = 1 << 31;
    
    /* shift past msb of 32-bit word */
    int beyond_msb = 1 << 31 << 1;
    
    /* set_msb is non-zero when word size >= 32
     * beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

// C
int int_size_is_32_mod_2 () {
    /* set msb of 32-bit machines */
    int set_msb = 1 << 15 << 15 << 1;
    
    /* shift past msb of 32-bit word */
    int beyond_msb = 1 << 15 << 15 << 2;
    
    /* set_msb is non-zero when word size >= 32
     * beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

main () {
    printf("%i\n", int_size_is_32_mod_2());
}
