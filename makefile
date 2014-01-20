all:
	g++ -c -g -Wall polynomial.cpp
	g++ -c -g -Wall polymain.cpp
	g++ -o polynomial polynomial.o polymain.o
	
	mv *.o polynomial bin
