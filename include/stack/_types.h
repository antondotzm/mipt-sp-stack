#ifndef _STACK_TYPES_H
#define _STACK_TYPES_H
#include "_defines.h"
typedef unsigned long long _stack_canary_t;

#if defined(_STACK_HASH_CONTENT) || defined(_STACK_HASH_STRUCT)
#include <djb2.h>
#endif

#include "_struct.h"
#endif
