# options to compile
OPTIONS = -D_TIME -D_TRAP_FPE -D_GNU_SOURCE

# compiler
CC = gcc

# C flags
CFLAGS = -Wall -march=native -Werror

# libs
LIBS = -ljpeg

# executable name
EXENAME = v4l2grab
# source files
SRCS = $(wildcard *.c)
# object files
OBJS = $(SRCS:%.c=%.o)
# header files
HDRS = $(wildcard *.h)

$(EXENAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(EXENAME) $(LIBS)

$(OBJS): $(HDRS) makefile

.PHONY: clean

clean:
	rm -f *.o *~ *.s *.il

%.o : %.c
	$(CC) $*.c -c $(CFLAGS)

