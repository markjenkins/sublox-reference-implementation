HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

sublox2: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
