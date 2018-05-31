all: test run

SRC = -L ~/workspace/src
INC = -I ~/workspace/include
CFLAG = -g -Wall

test: test.o
	g++ -o test test.o
test.o: test.cpp
	g++ -c test.cpp $(CFLAG) -c
	
run:
	./test
	
clean:
	rm -f test.o