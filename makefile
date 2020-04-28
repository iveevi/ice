tests: build
	g++ -std=c++11 chip.cpp main.cpp -g -o build/tests

build:
	mkdir build
