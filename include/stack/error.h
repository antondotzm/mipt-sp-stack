#ifndef _STACK_ERROR_H
#define _STACK_ERROR_H

typedef enum {
  STACK_OK = 0,
  STACK_UNKNOWN = -1,
  // STACK_EMPTY=1
} StackErrorKind;

typedef struct {
  StackErrorKind kind;
} StackError;

const static StackError _STACK_ERROR_OK = {STACK_OK};
const static StackError _STACK_ERROR_UNKNOWN = {STACK_UNKNOWN};
// const static StackError _STACK_ERROR_EMPTY = {STACK_EMPTY};

#endif
