PROGRAM = kadai2
OBJS = kadai2.o my_string.o structured_function.o
CFLAGS = -Wall -g
CC = gcc $(CFLAGS)

.SUFFIXES: .c .o

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^
.c.o:
	$(CC) -c $<

.PHONY :clean
clean:
	rm -f $(OBJS)

kadai2.o: kadai2.c my_string.h structured_function.h
my_string.o: my_string.c
structured_function.o: structured_function.c my_string.h \
  structured_function.h
