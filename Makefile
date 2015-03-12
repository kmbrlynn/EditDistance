CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: ED

ED: EditDistance.o ED.o
	$(CC) $(CFLAGS) -o ED EditDistance.o ED.o -lsfml-system

EditDistance.o: EditDistance.cpp ED.cpp
	$(CC) $(CFLAGS) -c EditDistance.cpp

ED.o: ED.cpp ED.hpp
	$(CC) $(CFLAGS) -c ED.cpp

clean:
	rm -rf ED *.o *.~
