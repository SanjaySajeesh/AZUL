.default: all

all: azul

clean:
	rm -f azul *.o

azul: Factory.o Node.o LinkedList.o  Player.o TileSet.o GameEngine.o Conversion.o Menu.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^


