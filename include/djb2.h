#ifndef _DJB2_H
#define _DJB2_H
typedef unsigned long djb2_t;

static inline djb2_t djb2(const unsigned char *buf, const unsigned char *end) {
  djb2_t hash = 5381;

  while (buf < end) {
    hash = hash * 33 + *(buf++);
  }

  return hash;
}

#endif
