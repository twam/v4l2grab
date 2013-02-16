# options to compile
OPTIONS = 

# compiler
CC = gcc

# C flags
CFLAGS = -Wall -Werror

# libs
LIBS = -ljpeg -lv4lconvert -lv4l2

# executable name
EXENAME = v4l2grab
# source files
SRCS = $(wildcard *.c)
# object files
OBJS = $(SRCS:%.c=%.o)
# header files
HDRS = $(wildcard *.h)
# git version 
GITVERSION = "$(shell git describe --always --tags --dirty)"


$(EXENAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(OPTIONS) -o $(EXENAME) $(LIBS)

$(OBJS): $(HDRS) makefile

.PHONY: clean

clean:
	rm -f *.o *~ *.s *.il

%.o : %.c
	$(CC) $*.c -c $(CFLAGS) $(OPTIONS) -D__GITVERSION='$(GITVERSION)'

