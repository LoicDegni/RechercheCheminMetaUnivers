OPTIONS = -O2 -Wall -Wextra -std=c++17    # pour optimiser
OBJ = tp3.o univers.o coordonnees.o tp3

all: tp3

tp3: tp3.o univers.o coordonnees.o
	g++ ${OPTIONS} -o tp3 tp3.o univers.o coordonnees.o

tp3.o: tp3.cpp 
	g++ ${OPTIONS} -c tp3.cpp

univers.o: univers.cpp
	g++ ${OPTIONS} -c univers.cpp

coordonnees.o: coordonnees.cpp
	g++ ${OPTIONS} -c coordonnees.cpp

clean:
	rm -rf $(OBJ)

