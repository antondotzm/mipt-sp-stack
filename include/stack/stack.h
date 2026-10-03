/* _STACK_CANARY_STRUCTBEGIN,_STACK_CANARY_STRUCTEND (_STACK_CANARY_STRUCT) -
 * канарейка по структуре стека
 * _STACK_HASH_CONTENT, _STACK_HASH_STRUCT
 * _STACK_CANARY_CONTENTBEGIN,_STACK_CANARY_CONTENTEND (_STACK_CANARY_CONTENT) -
 * канарейка по содержимому стека
 * _STACK_DEBUG
 * _STACK_CANARY_DYNAMIC
 */
#ifndef _STACK_H
#define _STACK_H
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "_defines.h"

#include "_struct.h"

#include "error.h"
#include "_debug.h"
#include "_canary.h"
// #include "_debug.h"




#define STACK_MIN_REALLOC_CAPACITY 8
static inline size_t max(size_t a, size_t b) {return (a>b)?a:b;}


StackError stack_with_capacity(struct Stack *self, const size_t capacity,
                               const size_t element_size);
/*
 * Make public if _STACK_HASH_CONTENT is disabled
 */
void *_stack_push_uninit(struct Stack *self);

void *stack_push(struct Stack *self, void* elem);
StackError stack_pop(struct Stack *self, void *elem);

#ifndef _STACK_HASH_CONTENT
// const void *stack_get(const struct Stack *self, size_t index);
// void *stack_get_mut(struct Stack *self, size_t index);
#endif

StackError stack_resize(struct Stack *self, const size_t new_capacity);
size_t stack_size(const struct Stack *self);
size_t stack_capacity(const struct Stack *self);
void stack_free(struct Stack *self);

#include "_sec.h"


static inline char stack_is_ok(const StackError err) {
  return err.kind == STACK_OK;
}

#endif // _STACK_H
