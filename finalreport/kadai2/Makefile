PROGRAM = kadai2
OBJS = kadai2.o my_string.o tree_function.o lifegame.o kadai2_ext.o char_rule.o my_math.o
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

kadai2.o: kadai2.c my_string.h tree_function.h lifegame.h char_rule.h \
  kadai2_ext.h
my_string.o: my_string.c
tree_function.o: tree_function.c my_string.h tree_function.h kadai2_ext.h
lifegame.o: lifegame.c tree_function.h lifegame.h kadai2_ext.h
char_rule.o: char_rule.c kadai2_ext.h my_math.h
kadai2_ext.o: kadai2_ext.c
my_math.o: my_math.h
