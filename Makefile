CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: EditDistance

EditDistance: EditDistance.o ED.o
	$(CC) $(CFLAGS) -o EditDistance EditDistance.o ED.o

EditDistance.o: EditDistance.cpp ED.cpp
	$(CC) $(CFLAGS) -c EditDistance.cpp

ED.o: ED.cpp ED.hpp
	$(CC) $(CFLAGS) -c ED.cpp

clean:
	rm -rf EditDistance *.o *.~
