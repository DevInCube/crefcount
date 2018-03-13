#pragma once

#include <assert.h>
#include <stdio.h>

typedef struct __Object Object;
typedef void (*DestructorFunction)(void *);

#define Object_new(DESTRUCTOR) __Object_new((DestructorFunction)DESTRUCTOR)
#define Object_free(OBJECT)    __Object_free(OBJECT)

#define Ref_incref(REF)        (__typeof__(REF))__Ref_incref((Object **)REF)
#define Ref_decref(REF)        (__typeof__(REF))__Ref_decref((Object **)REF)

#define AUTOREF                __attribute__((cleanup(__Ref_autodec)))

#define new(TYPE, ...)         __extension__({ TYPE * __ = malloc(sizeof(TYPE)); *__ = (TYPE)__VA_ARGS__; __; })

#define error(MESSAGE)         { assert(0 && MESSAGE); fprintf(stderr, MESSAGE); }

//
// do not use these functions directly

Object * __Object_new   (DestructorFunction destructor);
void     __Object_free  (Object * self);
void *   __Ref_incref   (Object ** ref);
void *   __Ref_decref   (Object ** ref);
void     __Ref_autodec  (void * refPtr);