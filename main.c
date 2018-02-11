#include <stdlib.h>
#include <stdio.h>
#include <progbase/console.h>
#include <module.h>

int main(void) {
    Console_clear();
    Console_setCursorAttribute(BG_INTENSITY_GREEN);
    test();
    printf("Welcome!\n\n");
    Console_reset();
    return 0;
}