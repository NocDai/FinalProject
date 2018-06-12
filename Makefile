all: clean main run

SRC = -L ./src                                                                                                                                                                                                                                                                                       
INC = -I ./include
CFLAG = -g -Wall

main: main.o controller.o player.o
	g++ -o main main.o controller.o player.o -lncurses
	
main.o:
	g++ -c ./src/main.cpp $(INC) $(CFLAG)

controller.o:
	g++ -c ./src/controller.cpp $(INC) $(CFLAG)
	
player.o:
	g++ -c ./src/player.cpp $(INC) $(CFLAG)

run:
	./main ./include/map.txt
	
clean:
	rm -f main.o controller.o player.o main 