CC = gcc
CFLAGS = -Wall -I
LDFLAGS =
OBJFILES = main.o parser.o
TARGET = main

/* very similar to the Makefiles we used for previous projects */
/* one difference is that we have it compile both main.c and parser.c */
all: $(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS -o $(TARGET) $(OBJFILES) $(LDFLAGS)


/* will delete the target file main and all the leftover intermediate object files that end .o */
clean:
	rm -f $(OBJFILES) $(TARGET) *~