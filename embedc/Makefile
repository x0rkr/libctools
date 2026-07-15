.PHONY: all clean

CC := gcc
CFLAGS := -Wall -Wextra -O2 -Iinclude

# Define all object files needed for the embedded module
OBJS :=src/io.o src/ring_buffer.o src/mempool.o
SRCS := src/io.c src/ring_buffer.c src/mempool.c

all: libctools_emb.o

# Link the individual object files into one partial-linked binary
libctools_emb.o: $(OBJS)
	ld -r $(OBJS) -o $@

# Pattern rule to compile any .c file in src/ into a .o file
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f libctools_emb.o src/*.o