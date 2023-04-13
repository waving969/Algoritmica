p2: Punto.o Practica2.o
	g++ -o p2 Punto.o Practica2.o

p2debug: Punto.o Practica2.o
	g++ -o p2debug Punto.o Practica2.o -std=c99 -Wall -DTEST --debug

Punto.o: Punto.cpp
	g++ -o Punto.o -c Punto.cpp

Practica2.o: Practica2.cpp Punto.hpp
	g++ -o Practica2.o -c Practica2.cpp

clean:
	rm *.o