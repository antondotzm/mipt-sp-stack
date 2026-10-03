#ifndef _STACK_DEFINES_H
#define _STACK_DEFINES_H

#ifdef _STACK_SEC_ALL
#ifndef _STACK_HASH_ALL
#define _STACK_HASH_ALL
#endif

#ifndef _STACK_CANARY_ALL
#define _STACK_CANARY_ALL
#endif
#ifndef _STACK_CANARY_DYNAMIC
// #define _STACK_CANARY_DYNAMIC
#endif
#endif // if _STACK_SEC_ALL

#ifdef _STACK_HASH_ALL
#ifndef _STACK_HASH_CONTENT
#define _STACK_HASH_CONTENT
#endif
#ifndef _STACK_HASH_STRUCT
#define _STACK_HASH_STRUCT
#endif
#endif // if _STACK_HASH_ALL

#ifdef _STACK_CANARY_ALL
#ifndef _STACK_CANARY_CONTENT
#define _STACK_CANARY_CONTENT
#endif
#ifndef _STACK_CANARY_STRUCT
#define _STACK_CANARY_STRUCT
#endif
#endif // if _STACK_CANARY_ALL

#ifdef _STACK_CANARY_CONTENT
#ifndef _STACK_CANARY_CONTENTBEGIN
#define _STACK_CANARY_CONTENTBEGIN
#endif
#ifndef _STACK_CANARY_CONTENTEND
#define _STACK_CANARY_CONTENTEND
#endif
#endif // if _STACK_CANARY_CONTENT

#ifdef _STACK_CANARY_STRUCT
#ifndef _STACK_CANARY_STRUCTBEGIN
#define _STACK_CANARY_STRUCTBEGIN
#endif
#ifndef _STACK_CANARY_STRUCTEND
#define _STACK_CANARY_STRUCTEND
#endif
#endif // if _STACK_CANARY_STRUCT

#ifdef _STACK_CANARY_DYNAMIC
#error "Dynamic canary is not yet implemented"
#endif

#endif
