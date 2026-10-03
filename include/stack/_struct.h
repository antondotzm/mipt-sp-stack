#ifndef _STACK_STRUCT_H
#define _STACK_STRUCT_H
#include "_types.h"

struct Stack {
#ifdef _STACK_CANARY_STRUCTBEGIN
  _stack_canary_t _canary_begin;
#endif

  void *begin;
  void *current;
  void *end;
  size_t element_size;

#ifdef _STACK_CANARY_STRUCTEND
  _stack_canary_t _canary_end;
#endif

#ifdef _STACK_HASH_CONTENT
  djb2_t _hash_content;
#endif
#ifdef _STACK_HASH_STRUCT
  djb2_t _hash_struct;
#endif
};

#endif
