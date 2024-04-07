all:
	sudo rm main
	g++  -std=c++14 -Wall -I/usr/include src/main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system 
	./main