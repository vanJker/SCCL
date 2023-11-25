#
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#

CC = g++

CFLAGS = -fno-builtin

OBJS = main.o util.o scan.o parse.o

# tiny.exe: $(OBJS)
tiny.out: $(OBJS)
#	$(CC) $(CFLAGS) -etiny $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# main.obj: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
main.o: main.cpp globals.h util.h scan.h parse.h
	$(CC) $(CFLAGS) -c $<

util.o: util.cpp util.h globals.h
	$(CC) $(CFLAGS) -c $<

scan.o: scan.cpp scan.h util.h globals.h
	$(CC) $(CFLAGS) -c $<

parse.o: parse.cpp parse.h scan.h globals.h util.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf tiny.out
	rm -rf $(OBJS)

tiny: tiny.out

all: tiny 

test:
	python test.py
