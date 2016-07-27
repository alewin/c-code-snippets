LDFLAGS=-pthread
CFLAGS=-g

SRC=$(wildcard *.c)
EXECUTABLE=$(SRC:%.c=../bin/%)

.PHONY: clean

all: $(EXECUTABLE)
clean:
	$(RM) $(EXECUTABLE)

../bin/%: %.c
	mkdir -p ../bin
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

test: $(EXECUTABLE)
	$(foreach var, $(EXECUTABLE), $(var);)
