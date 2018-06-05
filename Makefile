
all: main run

SRC = -L ./src                                                                                                                                                                                                                                                                                       
INC = -I ./include
CFLAG = -g -Wall

main: main.o
	g++ -o main main.o
main.o:
	g++ -c ~/workspace/FinalProject/include/main.cpp

run:
	./main ./include/map.txt
	
clean:
	rm -f main.o main