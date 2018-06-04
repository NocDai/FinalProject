##

all: test run

SRC = -L ./src                                                                                                                                                                                                                                                                                       
INC = -I ./include
CFLAG = -g -Wall

test: test.o
	g++ -o test test.o
	
test.o: test.cpp
	g++ -c test.cpp $(CFLAG) -c
	
test2: test2.o
	g++ -o test2 test2.o
test2.o: test2.cpp
	g++ -c test2.cpp
	
run:
	./test
	
clean:
	rm -f test.o test2.o