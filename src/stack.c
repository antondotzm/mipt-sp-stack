#include <stack/stack.h>
#include <stdio.h>
#include <string.h>

StackError stack_with_capacity(struct Stack *self, const size_t capacity,
                               const size_t element_size) {
  assert(self != NULL);
  assert(element_size > 0);
  assert(self->begin == NULL);
  self->begin = calloc(capacity * element_size + STACK_CANARY_CONTENT_SIZE, 1);
  if (self->begin == NULL)
    return _STACK_ERROR_UNKNOWN;
  self->begin = (void *)((char *)self->begin + STACK_CANARY_CONTENTBEGIN_SIZE);
  self->current = self->begin;
  self->end = (void *)((char *)self->begin + capacity * element_size);
  self->element_size = element_size;
  _stack_fill_sec(self);
  _stack_check(self);
  return _STACK_ERROR_OK;
}
/*
 * If realloc failed, old memory block stored
 *
 */
StackError stack_resize(struct Stack *self, const size_t new_capacity) {
  _stack_check(self);
  // const char *end = (const char *)self->end;
  const char *cur = (const char *)self->current;
  char *begin = (char *)self->begin;
  size_t old_size = (size_t)(cur - begin);
  // size_t old_cap = (size_t)(end - begin);
  assert(new_capacity * self->element_size >= old_size);
  self->begin =
      realloc((void *)(begin - STACK_CANARY_CONTENTBEGIN_SIZE),
              new_capacity * self->element_size + STACK_CANARY_CONTENT_SIZE);
  if (self->begin == NULL) {
    self->begin = (void *)begin;
    return _STACK_ERROR_UNKNOWN;
  }
  self->begin = (void *)((char *)self->begin + STACK_CANARY_CONTENTBEGIN_SIZE);
  self->end = (void *)(self->begin + new_capacity * self->element_size);
  self->current = (void *)(self->begin + old_size);
  _stack_update_sec(self);
  _stack_check(self);
  return _STACK_ERROR_OK;
}

// Must update content hash after
void *_stack_push_uninit(struct Stack *self) {
  _stack_check(self);
  if (self->current >= self->end) {
    assert(self->current == self->end);
    const size_t new_capacity =
        max(stack_capacity(self) * 2, STACK_MIN_REALLOC_CAPACITY);
    stack_resize(self, new_capacity);
  }
  void *result = self->current;
  self->current = (void *)((char *)self->current + self->element_size);

#ifdef _STACK_CANARY_CONTENTEND
  _stack_fill_canary_contentend(self);
#endif

#ifdef _STACK_HASH_STRUCT
  _stack_fill_struct_hash(self);
#endif
// Do not check because _stack_fill_content_hash is not called
  // _stack_check(self);
  return result;
}
void *stack_push(struct Stack *self, void *elem) {
  _stack_check(self);
  void *new_elem = _stack_push_uninit(self);
  memmove(new_elem, elem, self->element_size);
#ifdef _STACK_HASH_CONTENT
  _stack_fill_content_hash(self);
#endif
#ifdef _STACK_HASH_STRUCT
  _stack_fill_struct_hash(self);
#endif
  _stack_check(self);
  return new_elem;
}

StackError stack_pop(struct Stack *self, void *elem) {
  _stack_check(self);
  $stack_assert(self, (char *)self->current >=
                          self->element_size + (char *)self->begin);
  self->current = (void *)((char *)self->current - self->element_size);
  memmove(elem, self->current, self->element_size);

#ifdef _STACK_CANARY_CONTENTEND
  _stack_fill_canary_contentend(self);
#endif
#ifdef _STACK_HASH_CONTENT
  _stack_fill_content_hash(self);
#endif
#ifdef _STACK_HASH_STRUCT
  _stack_fill_struct_hash(self);
#endif
  return _STACK_ERROR_OK;
}

// const void *stack_get(const struct Stack *self, size_t index) {
//   _stack_check(self);
//   const char *begin = (const char *)self->begin;
//   const void *element = (void *)(begin + index * self->element_size);
//   assert(element < self->current);
//   return element;
// }

/// if _STACK_HASH_CONTENT is defined: after editing content call
/// stack_fill_content_hash
// void *stack_get_mut(struct Stack *self, size_t index) {
//   _stack_check(self);
//   char *begin = (char *)self->begin;
//   void *element = (void *)(begin + index * self->element_size);
//   assert(element < self->current);
//   return element;
// }

size_t stack_size(const struct Stack *self) {
  _stack_check(self);
  return ((const char *)self->current - (const char *)self->begin) /
         self->element_size;
}
size_t stack_capacity(const struct Stack *self) {
  _stack_check(self);
  return ((const char *)self->end - (const char *)self->begin) /
         self->element_size;
}

void stack_free(struct Stack *self) {
  _stack_check(self);
  if (self->begin) {
    void *begin =
        (void *)((char *)self->begin - STACK_CANARY_CONTENTBEGIN_SIZE);
    if (begin)
      free(begin);
  }
  self->begin = NULL;
  self->end = NULL;
  self->current = NULL;
  self->element_size = 0;
}
