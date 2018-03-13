#include <stdio.h>
#include <assert.h>
#include <list.h>
#include <object.h>

struct __List {
    Object *  object;  // enable ref count
    void **   array;
    size_t    capacity;
    size_t    length;
};

static const size_t LIST_INITIAL_CAPACITY = 16;

static void List_free(List * self);

List *   List_new(void) {
    return new(List, {
        .object = Object_new(List_free),
        .capacity = LIST_INITIAL_CAPACITY,
        .array = malloc(sizeof(void *) * LIST_INITIAL_CAPACITY),
        .length = 0
    });
}
static void     List_free(List * self) {
    Object_free(self->object);
    List_clear(self);
    free(self->array);
    free(self);
}

static void ensureCapacity(List * self) {
    if (self->length >= self->capacity - 1) {
        size_t newCapacity = self->capacity * 2;
        void * newArray = realloc(self->array, sizeof(void *) * newCapacity);
        if (newArray == NULL) {
            error("Out of Memory at List realloc");
            return;
        }
        self->capacity = newCapacity;
        self->array = newArray;
    }
}

static void insert(List * self, void * value, size_t index) {
    assert(index <= self->length);
    ensureCapacity(self);
    for (int i = self->length; i > index; i--) {
        self->array[i] = self->array[i - 1];
    }
    self->array[index] = value;
    self->length++;
}

void     List_insert(List * self, void * value, size_t index) {
    insert(self, value, index);
    Ref_incref(value); // keep this ref, so incref
}
void     List_insertNew(List * self, void * value, size_t index) {
    insert(self, value, index);
    // keep this ref, but no incref (stealing ref)
}
void     List_add(List * self, void * value) {
    List_insert(self, value, self->length);
}
void     List_addNew(List * self, void * value) {
    List_insertNew(self, value, self->length);
}
void * List_at(List * self, size_t index) {
    assert(index < self->length);
    return self->array[index];  // borrowed ref
}
void List_removeAt(List * self, size_t index) {
    assert(index < self->length);
    void * oldValue = self->array[index];
    for (int i = index + 1; i < self->length; i++) {
        self->array[i - 1] = self->array[i];
    }
    self->length--;
    Ref_decref(oldValue);  // decref, we release our reference
}
void List_clear(List * self) {
    for (int i = self->length - 1; i >= 0; i--) {
        List_removeAt(self, i);
    }
}
size_t   List_count(List * self) {
    return self->length;
}