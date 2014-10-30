all: luvri

luvri: main.o motor.o tablero_mov.o
	g++ main.o motor.o tablero_mov.o -o luvri

main.o: main.cpp
	g++ -c main.cpp

motor.o: motor.cpp
	g++ -c motor.cpp

tablero_mov.o: tablero_mov.cpp
	g++ -c tablero_mov.cpp

clean:
	rm -rf *\.o luvri
