#ifndef _STACK_SEC_H
#define _STACK_SEC_H
#include "_debug.h"
#include "_struct.h"
#include "_check.h"
#include "stack.h"

static inline void _stack_fill_sec(struct Stack *self);
static inline void _stack_check(const struct Stack *self);



static inline void _stack_update_sec(struct Stack *self) {
// partially check_canary
#ifdef _STACK_HASH_CONTENT
  _stack_fill_content_hash(self);
#endif
#ifdef _STACK_HASH_STRUCT
  _stack_fill_struct_hash(self);
#endif
}

static inline void _stack_fill_sec(struct Stack *self) {
#ifdef _STACK_CANARY_STRUCTBEGIN
  self->_canary_begin = _STACK_CANARY_BASE;
#endif
#ifdef _STACK_CANARY_STRUCTEND
  self->_canary_end = _STACK_CANARY_BASE;
#endif

#ifdef _STACK_CANARY_CONTENTBEGIN
_stack_fill_canary_contentbegin(self);
#endif
#ifdef _STACK_CANARY_CONTENTEND
_stack_fill_canary_contentend(self);
#endif

#ifdef _STACK_HASH_CONTENT
  _stack_fill_content_hash(self);
#endif
#ifdef _STACK_HASH_STRUCT
  _stack_fill_struct_hash(self);
#endif
} // end _stack_fill_sec

#define _stack_check(self) do{ \
  $stack_assert(self, self != NULL); \
  $stack_assert(self, self->begin!=NULL); \
  $stack_assert(self, self->current >= self->begin); \
  $stack_assert(self, self->end >= self->current); \
  $stack_assert(self, self->element_size != 0); \
  $stack_assert(self, \
                ((const char *)self->current - (const char *)self->begin) % \
                        self->element_size == \
                    0); \
 \
  $stack_assert(self, _stack_check_canary_structbegin(self)!=0); \
  $stack_assert(self, _stack_check_canary_structend(self)!=0); \
 \
  $stack_assert(self, _stack_check_canary_contentbegin(self)!=0); \
  $stack_assert(self, _stack_check_canary_contentend(self)!=0); \
    $stack_assert(self, _stack_check_struct_hash(self) != 0); \
    $stack_assert(self, _stack_check_content_hash(self) != 0); \
}while(0);

#endif
