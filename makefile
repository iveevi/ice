tests: build
	g++ -std=c++11 main.cpp chip.cpp standard.cpp -g -o build/tests

build:
	mkdir build
