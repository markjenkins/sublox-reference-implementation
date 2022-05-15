HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

clox: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
