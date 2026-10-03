#ifndef _STACK_CANARY_H
#define _STACK_CANARY_H
#include "_types.h"
#include <stddef.h>
#include <string.h>

struct Stack;

const static _stack_canary_t _STACK_CANARY_BASE = 0xDEADBEEFCAFEBABE;
const static size_t _STACK_CANARY_SIZE = sizeof(_stack_canary_t);

#ifdef _STACK_CANARY_CONTENTBEGIN
const static size_t STACK_CANARY_CONTENTBEGIN_SIZE = _STACK_CANARY_SIZE;
static inline void _stack_fill_canary_contentbegin(struct Stack *self) {
  void *real_begin = (void *)((char *)self->begin - _STACK_CANARY_SIZE);
  *(_stack_canary_t *)real_begin = _STACK_CANARY_BASE;
}
static inline char _stack_check_canary_contentbegin(const struct Stack *self) {
  void *real_begin = (void *)((char *)self->begin - _STACK_CANARY_SIZE);
  return *(_stack_canary_t *)real_begin == _STACK_CANARY_BASE;
}
#else
const static size_t STACK_CANARY_CONTENTBEGIN_SIZE = 0;
static inline void _stack_fill_canary_contentbegin(struct Stack *_) {}
static inline char _stack_check_canary_contentbegin(const struct Stack *_) {
  return 1;
}
#endif // ifdef _STACK_CANARY_CONTENTBEGIN

#ifdef _STACK_CANARY_CONTENTEND
const static size_t STACK_CANARY_CONTENTEND_SIZE = _STACK_CANARY_SIZE;
static inline void _stack_fill_canary_contentend(struct Stack *self) {
  memcpy(self->current, &_STACK_CANARY_BASE, _STACK_CANARY_SIZE);
}
static inline char _stack_check_canary_contentend(const struct Stack *self) {
  return memcmp(self->current, &_STACK_CANARY_BASE, _STACK_CANARY_SIZE) == 0;
}
#else
const static size_t STACK_CANARY_CONTENTEND_SIZE = 0;
static inline void _stack_fill_canary_contentend(struct Stack *_) {}
static inline char _stack_check_canary_contentend(const struct Stack *_) {
  return 1;
}
#endif // ifdef _STACK_CANARY_CONTENTEND

const static size_t STACK_CANARY_CONTENT_SIZE =
    STACK_CANARY_CONTENTBEGIN_SIZE + STACK_CANARY_CONTENTEND_SIZE;

#ifdef _STACK_CANARY_STRUCTBEGIN
static inline void _stack_fill_canary_structbegin(struct Stack *self) {
  self->_canary_begin = _STACK_CANARY_BASE;
}
static inline char _stack_check_canary_structbegin(const struct Stack *self) {
  return self->_canary_begin == _STACK_CANARY_BASE;
}
#else
static inline void _stack_fill_canary_structbegin(struct Stack *_) {}
static inline char _stack_check_canary_structbegin(const struct Stack *_) {
  return 1;
}
#endif // if _STACK_CANARY_STRUCTBEGIN

#ifdef _STACK_CANARY_STRUCTEND
static inline void _stack_fill_canary_structend(struct Stack *self) {
  self->_canary_end = _STACK_CANARY_BASE;
}
static inline char _stack_check_canary_structend(const struct Stack *self) {
  return self->_canary_end == _STACK_CANARY_BASE;
}
#else
static inline void _stack_fill_canary_structend(struct Stack *_) {}
static inline char _stack_check_canary_structend(const struct Stack *_) {
  return 1;
}

#endif // if _STACK_CANARY_STRUCTEND

#endif // if _STACK_CANARY_H
