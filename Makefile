CFLAGS = -Wall -g --std=c99

objs:= polynomial.o polydiv polymulti polysum polydiff

all: $(objs)

polymulti: polynomial.o

polydiv: polynomial.o

polysum: polynomial.o

polydiff: polynomial.o

clean:
	rm -rf $(objs)
