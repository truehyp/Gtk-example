CC = gcc
program = cairo-example1
LDLIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`

$(program):$(program).o
	$(CC) $(LDLIBS) $(program).o -o $(program)

$(program).o:$(program).c
	$(CC) $(CFLAGS) -c $(program).c

clean :
	-rm -f $(program)
	-rm -f *.o

