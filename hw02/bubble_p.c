// bubble_p.c
#include <stdio.h>
#include <stdlib.h>

/* Bubble sort, referencing array elements with pointers rather than indexing */
void bubble_p(int *data, int count) {
    int i, last;
    int *x, *y;
    for (last = count-1; last > 0; last--) {
        for (i = 0; i < last; i++) {
            x = data + i;
            y = data + i + 1;
            if (*x > *y) {
                /* Swap adjacent elements */
                int t = *y;
                *y = *x;
                *x = t;
            }
        }
    }
}

/* prototype assembly function using goto */
void bubble_p_asm(int *data, int count) {
    int eax, ebx, ecx, edx;
    int esp;
    int a, b;
    eax = count - 1; // eax = last
    
    if (eax <= 0)
        goto exit;

 outer_loop: 
    // outer loop body
    // init inner loop
    ecx = 0;         // ecx = i
    if (eax <= ecx)
        goto outer_loop_update;

 inner_loop: 
    // inner loop body
    esp = ecx;
    edx = (int) (data + ecx + 1);
    ecx = (int) (data + ecx);
    a = *(int*)ecx;
    b = *(int*)edx;
    if (b >= a)
        goto pop_ecx;

 swap:
    *(int*)ecx = b;
    *(int*)edx = a;
    
 pop_ecx:
    ecx = esp;
         
    // inner loop body end
        
    ecx = ecx + 1; // update inner loop counter
    if (ecx < eax)
        goto inner_loop;

    
    // outerloop body end
 outer_loop_update:
    eax = eax - 1; // update outer loop counter
    if (eax > 0)
        goto outer_loop;

 exit:
    return;
}

int main() {
    int i, n, c;
    int udata[10], sdata[10];
    
    // loop c time (c for coverage)
    for (c = 0; c < 5; c++) {
        // generate random data
        for (i = 0; i < 10; i++) {
            n = rand() % 20;
            udata[i] = n;
            sdata[i] = n;
        }
        // sort data
        bubble_p_asm(sdata, 10);
        
        // print result
        printf("\n\nUnsorted Data: ");
        for (i = 0; i < 10; i++)
            printf("%d ", udata[i]);
        printf("\nSorted Data: ");
        for (i = 0; i < 10; i++)
            printf("%d ", sdata[i]);
    }
    
    return 0;
}
        
