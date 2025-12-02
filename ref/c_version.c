#include <stdio.h>

int main() {
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ == 201710L
            printf("Using C17 standard.\n");
        #elif __STDC_VERSION__ == 201112L
            printf("Using C11 standard.\n");
        #elif __STDC_VERSION__ == 199901L
            printf("Using C99 standard.\n");
        #else
            printf("Using a different C standard (version: %ld).\n", __STDC_VERSION__);
        #endif
    #else
        printf("Using C89/C90 standard (or a pre-C99 standard).\n");
    #endif
    return 0;
}
