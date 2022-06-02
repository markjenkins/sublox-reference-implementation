HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

sublox: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
