CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp tablero_mov.cpp motor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=luvri

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *\.o luvri
