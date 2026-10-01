#ifndef _DJB2_H
#define _DJB2_H
typedef unsigned long djb2_t;


static inline djb2_t djb2_update(const unsigned char *buf, const unsigned char *end, djb2_t init_value)
{
    djb2_t hash = init_value;
    while (buf < end) {
      hash = hash * 33 + *(buf++);
    }

    return hash;
}

static inline djb2_t djb2(const unsigned char *buf, const unsigned char *end) {
    return djb2_update(buf,end,5381);
}


#endif
