CFLAGS:=-fPIC -O3 -g -Wall -Wextra -Iinclude -fsanitize=address,undefined -std=c11 -D_STACK_SEC_ALL -D_STACK_DEBUG
BUILDDIR:=dist
DISTDIR:=dist
CC:=clang

build:
	$(CC) $(CFLAGS) src/stack.c -c -o $(BUILDDIR)/stack.o
	ar r $(DISTDIR)/stack.a $(BUILDDIR)/stack.o
	$(CC) $(CFLAGS) src/main.c -c -o $(BUILDDIR)/main.o
	$(CC) $(CFLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/stack.o -o $(DISTDIR)/main

fmt:
	clang-format -i tests/*.c
	clang-format -i src/*.c
	clang-format -i include/*.h
	clang-format -i include/stack/*.h

run:
	$(MAKE) build
	$(DISTDIR)/main

test:
	$(MAKE) build
	$(CC) $(CFLAGS) tests/main.c $(DISTDIR)/stack.a -o $(DISTDIR)/test_main
	$(CC) $(CFLAGS) tests/djb2.c $(DISTDIR)/stack.a -o $(DISTDIR)/test_djb2
	$(DISTDIR)/test_djb2
	$(DISTDIR)/test_main
