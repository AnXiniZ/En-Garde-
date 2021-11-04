CC=gcc
CFLAGS=-I.
DEPS=main.h
SOURCES=main.c general.c player.c bot.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=engarde

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CLAGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)