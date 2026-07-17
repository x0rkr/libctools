.PHONY: all clean

CC := gcc
CFLAGS := -Wall -Wextra -O2 -Iinclude
AR := ar


SRCS := src/format.c src/string.c src/vector.c src/hashtable.c
OBJS := $(SRCS:.c=.o)

TARGET := libctools_std.a

all: $(TARGET)


$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)