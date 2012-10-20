#include <stdio.h>

int main(int argc, char** argv) {
    int x = 0x12345678;
    int y = 0x87654321;
    int mask = 0x000000FF;
    int result = x & mask;              // result = 0x00000078
    
    int a = 10;
    int b = 11;
    int mask2 = b < a;
    // mask2 = (b < a) ? 1 : 0
    
    int cond = (mask2 << 31) >> 31;
    // cond = (mask2) ? 0xFFFFFFF : 0x0000000
    
    int z = (x & cond) | (y & ~cond);
    // z = (b < a) ? x : a

    printf("%X\n", z);
    printf("%X\n", (0x1 << 31 >> 31 >> 8));
}
    
    
