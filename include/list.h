#pragma once

#include <stdlib.h>
#include <object.h>

typedef struct __List List;

List *   List_new      (void);
// destructor is hidden as we enable ref count for List

void     List_insert   (List * self, void * value, size_t index);
void     List_insertNew(List * self, void * value, size_t index);  // stealing ref
void     List_add      (List * self, void * value);
void     List_addNew   (List * self, void * value);  // stealing ref
void *   List_at       (List * self, size_t index);
void     List_removeAt (List * self, size_t index);
void     List_clear    (List * self);
size_t   List_count    (List * self);