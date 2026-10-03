#ifndef _STACK_CHECK_H
#define _STACK_CHECK_H
#include "_struct.h"
#include "stack.h"

// Checks

#ifdef _STACK_HASH_STRUCT

static inline char _stack_check_struct_hash(const struct Stack *self) {
  const djb2_t old = self->_hash_struct;
  // self->_hash_struct = 0;
  const unsigned char *self_bytes = (const unsigned char *)self;
  const djb2_t real =
      djb2(self_bytes, self_bytes + sizeof(*self) - sizeof(self->_hash_struct));
  // self->_hash_struct = old;

  return old == real;
}

static inline djb2_t _stack_fill_struct_hash(struct Stack *self) {
  djb2_t old = self->_hash_struct;
  // self->_hash_struct = 0;
  const unsigned char *self_bytes = (const unsigned char *)self;
  self->_hash_struct =
      djb2(self_bytes, self_bytes + sizeof(*self) - sizeof(self->_hash_struct));
#ifdef _STACK_DEBUG
  $stack_assert(self, _stack_check_struct_hash(self) != 0);
#endif
  return old;
}
#else
static inline char _stack_check_struct_hash(const struct Stack *_) { return 1; }
#endif // _STACK_HASH_STRUCT

#ifdef _STACK_HASH_CONTENT
static inline djb2_t _stack_fill_content_hash(struct Stack *self) {
  djb2_t old = self->_hash_content;
  self->_hash_content = djb2(self->begin, self->end);
  return old;
}

static inline char _stack_check_content_hash(const struct Stack *self) {
  djb2_t real = djb2(self->begin, self->end);
  return real == self->_hash_content;
}
#else
static inline char _stack_check_content_hash(const struct Stack *_) {
  return 1;
}
#endif // if _STACK_HASH_CONTENT

#endif // if _STACK_CHECK_H
