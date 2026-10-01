#include <assert.h>
#include <stack/stack.h>
#include <stdio.h>

int main() {
  struct Stack s = {};
  assert(stack_is_ok(stack_with_capacity(&s, 30, 4)));
  int v = 4;
  stack_push(&s, &v);
  s.element_size = 2;
  // Would fail with assert
  stack_free(&s);
  printf("test main passed\n");

  return 0;
}
