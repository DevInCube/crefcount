#include <integer.h>
#include <stdlib.h>

static void Integer_free(Integer * self);

Integer * Integer_new(int value) {
    return new(Integer, {
        .object = Object_new(Integer_free),
        .value = value
    });
}

static void Integer_free(Integer * self) {
    Object_free(self->object);
    free(self);
}