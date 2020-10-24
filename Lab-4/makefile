#makefile

lab4: main.o heap.o
	g++ main.o heap.o -o lab4.exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
	
heap.o: heap.cpp
	g++ -std=c++11 -c heap.cpp

clear:
	rm main.o
	rm heap.o
