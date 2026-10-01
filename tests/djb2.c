#include <assert.h>
#include <djb2.h>
#include <stdio.h>
#include <string.h>

djb2_t djb2s(const char *s) {
  const char *e = s + strlen(s);
  return djb2(s, e);
}

int main() {
  assert(djb2s("") == 5381);
  assert(djb2s("\1") == 5381 * 33 + 1);

  printf("\n\ndjb2 passed\n\n\n");
  return 0;
}
