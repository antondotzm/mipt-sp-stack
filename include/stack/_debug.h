#ifndef _STACK_DEBUG_H
#define _STACK_DEBUG_H
#include "_defines.h"

#ifdef _STACK_DEBUG

static inline void stack_dump(const struct Stack *stack);

static inline void stack_assert_failed(const struct Stack *stack,
                                       const char *assertable, const int file,
                                       const int line);

#define $stack_assert(stack, assertable)                                       \
  if (!(assertable))                                                           \
    stack_assert_failed(stack, #assertable, __FILE__, __LINE__);
#else
#define $stack_assert(stack, assertable) assert(assertable);
#endif // if _STACK_DEBUG


/// Begin debug functions

#ifdef _STACK_DEBUG

static inline void stack_dump(const struct Stack *self) {}

static inline void stack_assert_failed(const struct Stack *self,
                                       const char *assertable, const int file,
                                       const int line) {
  fprintf(stderr, "Assertion(%d:%d) failed: %s\n", file, line, assertable);
  stack_dump(self);
  abort();
}
#endif // if _STACK_DEBUG

/// End debug functions

#endif // if _STACK_DEBUG_H
