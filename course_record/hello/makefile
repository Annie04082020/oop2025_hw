.PHONY: test clean

all: mkdir hello test

mkdir:
	mkdir -p bin

hello: src/hello.cpp src/generate_greeting.h
	g++ -std=c++20 src/hello.cpp -o bin/hello

test: test/test_main.cpp test/generate_greeting_test.h
	g++ -std=c++20 test/test_main.cpp -o bin/test -lgtest -lpthread

clean:
	rm -f bin/*