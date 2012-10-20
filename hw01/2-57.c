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
