CC = g++
CFLAGS = -c -g -Wall -o

OBJECTS = 	bin/polynomial.o	\
		bin/polymain.o
		
all: bin/polymain

bin/polymain: $(OBJECTS)
	$(CC) -o bin/polynomial $(OBJECTS) -lUnitTest++
	
bin/polynomial.o: polynomial.cpp
	$(CC) $(CFLAGS) bin/polynomial.o polynomial.cpp
	
bin/polymain.o: polymain.cpp
	$(CC) $(CFLAGS) bin/polymain.o polymain.cpp
	
clean:
	rm -f bin/*
