#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <object.h>

struct __Object {
    DestructorFunction destructor;
    int refCount;
};

Object * __Object_new   (DestructorFunction destructor) {
    assert(destructor != NULL);
    return new(Object, {
        .destructor = destructor,
        .refCount = 1
    });
}
void     Object_free  (Object * self) {
    assert(self != NULL);
    free(self);
}

void *   __Ref_incref(Object ** ref) {
    assert(ref != NULL);
    Object * self = *(Object **)ref;
    if (self->refCount > 0) {
        self->refCount++;
    } else {
        error("Trying to incref destroyed reference");
    }
    return ref;
}
void *   __Ref_decref(Object ** ref) {
    assert(ref != NULL);
    Object * self = *(Object **)ref;
    if (self->refCount > 0) {
        self->refCount--;
        if (self->refCount == 0) {
            if (self->destructor) {
                self->destructor((void *)ref);
            }
        }
    } else {
        error("Trying to decref destroyed reference");
    }
    return ref;
}

void __Ref_autodec(void * ptr) {
    if (ptr == NULL) return;
    Object *** opp = ptr;
    Ref_decref(*opp);
}