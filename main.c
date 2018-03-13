#include <stdlib.h>
#include <stdio.h>
#include <progbase/console.h>
#include <object.h>
#include <list.h>
#include <integer.h>

void printInts(List * list);

int main(void) {
    List * list AUTOREF = List_new();
    for (int i = 0; i < 10; i++) {
        List_addNew(list, Integer_new(i));  // steal new int ref
    }
    printInts(list);
    return 0; // list will be freed with decref as AUTOREF
}

void printInts(List * list) {
    for (int i = 0; i < List_count(list); i++) {
        Integer * integer = (Integer *)List_at(list, i);
        printf("%i, ", integer->value);
    }
    puts("");
}