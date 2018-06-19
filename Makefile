all: clean main run

S_PATH = ./src/
SRC = -L ./src                                                                                                                                                                                                                                                                                       
INC = -I ./include
CFLAG = -g -Wall

main: controller.o player.o map.o keyandpass.o main.o
	g++ -o main main.o controller.o player.o keyandpass.o map.o

main.o:
	g++ -c $(S_PATH)main.cpp $(INC) $(CFLAG)

controller.o:
	g++ -c $(S_PATH)controller.cpp $(INC) $(CFLAG)

player.o:
	g++ -c $(S_PATH)player.cpp $(INC) $(CFLAG)

map.o:
	g++ -c $(S_PATH)map.cpp $(INC) $(CFLAG)

keyandpass.o:
	g++ -c $(S_PATH)keyandpass.cpp $(INC) $(CFLAG)

run:
	./main ./include/map.txt

clean:
	rm -f main.o controller.o player.o map.o keyandpass.o main