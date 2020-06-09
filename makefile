chips:	build
	g++ -std=c++11 chip.cpp main.cpp -lpthread -g -o build/chips

build:
	mkdir build
