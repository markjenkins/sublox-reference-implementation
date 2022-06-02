HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

sublox1: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
