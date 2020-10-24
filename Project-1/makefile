#makefile

proj1: main.o matrix.o
	g++ main.o matrix.o -o proj1.exe

proj2: regression.o matrix.o
	g++ regression.o matrix.o -o proj2.exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

regression.o: regression.cpp
	g++ -std=c++11 -c regression.cpp

matrix.o: matrix.cpp matrix.h
	g++ -std=c++11 -c matrix.cpp matrix.h

clear:
	rm main.o
	rm regression.o
	rm matrix.o
