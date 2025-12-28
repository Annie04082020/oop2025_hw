.PHONY: clean

test: test/ut_main.cpp test/vector_test.h src/vector.h
	g++ -std=c++11 test/ut_main.cpp -o bin/ut -lgtest -lpthread

clean:
	rm -f bin/*