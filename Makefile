CFLAGS = -Wall -g --std=c99

objs:= polydiv polynomial.o

polydiv: polynomial.o

all: $(objs)

clean:
	rm -rf $(objs)
