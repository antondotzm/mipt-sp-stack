#include <assert.h>
#include <stack/stack.h>
#include <stdio.h>

int main() {
  struct Stack s = {};
  assert(stack_is_ok(stack_with_capacity(&s, 0, 5)));
  long v = 4;
  stack_push(&s, &v);
  stack_pop(&s, &v);
  stack_free(&s);
  printf("test main passed\n");

  return 0;
}
