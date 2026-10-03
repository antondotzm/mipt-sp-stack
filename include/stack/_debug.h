#ifndef _STACK_DEBUG_H
#define _STACK_DEBUG_H
#include "_defines.h"

#ifdef _STACK_DEBUG
#include <stddef.h>
#include <stdio.h>

enum StackSecBitsEnum {
  STACK_NULL_PTR = 1 << 0,
  STACK_NULL_BEGIN = 1 << 1,
  STACK_CURRENT_LT_BEGIN = 1 << 2,
  STACK_END_LT_CURRENT = 1 << 3,
  STACK_ZERO_EL_SIZE = 1 << 4, // 0x10
  // Stack size is not divisible by element size
  STACK_SIZE_NOT_MATCH_EL_SIZE = 1 << 5,
  STACK_BAD_STRUCT_CANARY_L = 1 << 6,
  STACK_BAD_STRUCT_CANARY_R = 1 << 7,

  STACK_BAD_CONTENT_CANARY_L = 1 << 8, // 0x100
  STACK_BAD_CONTENT_CANARY_R = 1 << 9,

  STACK_BAD_STRUCT_HASH = 1 << 10,
  STACK_BAD_CONTENT_HASH = 1 << 11, // 0x800
};
static inline long _stack_sec_mask(const struct Stack *self);

static inline void stack_dump(const struct Stack *stack);

static inline void stack_assert_failed(const struct Stack *self,
                                       const char *assertable, const char *file,
                                       const char *func, const int line);

#define $stack_assert(stack, assertable)                                       \
  if (!(assertable))                                                           \
    stack_assert_failed(stack, #assertable, __FILE__, __func__, __LINE__);
#else
#define $stack_assert(stack, assertable) assert(assertable);
#endif // if _STACK_DEBUG

/// Begin debug functions

#ifdef _STACK_DEBUG


static inline void stack_dump(const struct Stack *self) {
  long sec_mask = _stack_sec_mask(self);
  fprintf(stderr, "Stack.sec = %08lx\n", sec_mask);
  if (!self) {
    fprintf(stderr, "(Stack*)NULL\n");
    return;
  }
  fprintf(stderr, "Stack{begin=%p,current=%p,end=%p,element_size=%zu",
          self->begin, self->current, self->end, self->element_size);
#ifdef _STACK_HASH_STRUCT
  fprintf(stderr, ",hs=%08lx", self->_hash_struct);
#endif
#ifdef _STACK_HASH_CONTENT
  fprintf(stderr, ",hc=%08lx", self->_hash_content);
#endif
#ifdef _STACK_CANARY_STRUCTBEGIN
  fprintf(stderr, ",csl=%08llx", self->_canary_begin);
#endif
#ifdef _STACK_CANARY_STRUCTEND
  fprintf(stderr, ",csr=%08llx", self->_canary_end);
#endif
// Could crash
#ifdef _STACK_CANARY_CONTENTBEGIN
  // fprintf(stderr, ",ccl=%08x", self->_canary_begin);
#endif
#ifdef _STACK_CANARY_CONTENTEND
  // fprintf(stderr, ",ccr=%08x", self->_canary_end);
#endif
  fprintf(stderr, "}\n");
}

static inline void stack_assert_failed(const struct Stack *self,
                                       const char *assertable, const char *file,
                                       const char *func, const int line) {
  fprintf(stderr, "Assertion(%s:%s:%d) failed: %s\n", file, func, line,
          assertable);
  stack_dump(self);
  abort();
}



#include "_check.h"
static inline long _stack_sec_mask(const struct Stack *self) {
  long mask = 0;
  if (self==NULL) {
    return STACK_NULL_PTR;
  }
  if (!self->begin)
    mask |= STACK_NULL_BEGIN;
  if (self->current < self->begin)
    mask |= STACK_CURRENT_LT_BEGIN;
  if (self->end < self->current)
    mask |= STACK_END_LT_CURRENT;
  char content_ok = mask == 0;

  if (self->element_size == 0)
    mask |= STACK_ZERO_EL_SIZE;
  if (((const char *)self->current - (const char *)self->begin) %
          self->element_size !=
      0)
    mask |= STACK_SIZE_NOT_MATCH_EL_SIZE;

  mask |=
      STACK_BAD_STRUCT_CANARY_L * (_stack_check_canary_structbegin(self) == 0);
  mask |=
      STACK_BAD_STRUCT_CANARY_R * (_stack_check_canary_structend(self) == 0);

  if (content_ok) {
    mask |= STACK_BAD_CONTENT_CANARY_L *
            (_stack_check_canary_contentbegin(self) == 0);
    mask |= STACK_BAD_CONTENT_CANARY_R *
            (_stack_check_canary_contentend(self) == 0);
  }

  mask |= STACK_BAD_STRUCT_HASH * (_stack_check_struct_hash(self) == 0);
  if (content_ok) {
    mask |= STACK_BAD_CONTENT_HASH * (_stack_check_content_hash(self) == 0);
  }
  return mask;
}


#endif // if _STACK_DEBUG

/// End debug functions

#endif // if _STACK_DEBUG_H
