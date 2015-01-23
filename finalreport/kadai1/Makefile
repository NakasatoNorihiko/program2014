PROGRAM = kadai1
OBJS = kadai1.o my_string.o tree_function.o
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

kadai1.o: kadai1.c my_string.h tree_function.h
my_string.o: my_string.c
tree_function.o: tree_function.c my_string.h tree_function.h
