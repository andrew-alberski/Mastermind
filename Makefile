Mastermind: main.o
	g++ main.o -o Mastermind
main.o: main.cpp masterMind.h
	g++ -g -Wall -c main.cpp
clean: 
	rm main.o Mastermind
