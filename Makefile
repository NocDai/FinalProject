
all: clean main run

SRC = -L ./src                                                                                                                                                                                                                                                                                       
INC = -I ./include
CFLAG = -g -Wall

main: main.o
	g++ -o main main.o -lncurses
main.o:
	g++ -c ./include/main.cpp 

run:
	./main ./include/map.txt
	
clean:
	rm -f main.o main