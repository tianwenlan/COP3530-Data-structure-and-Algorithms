all: Proj4

Proj4: main.o set.o
	g++ -o Proj4 main.o set.o

main.o: main.cpp proj4.h
	g++ -c main.cpp



clean:
	rm -rf *.o Proj4
