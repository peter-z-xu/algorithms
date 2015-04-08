CC=g++
CFLAGS=-Wall -g
LDFLAGS=

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
EXECUTABLES := $(SOURCES:%.cpp=%)

all: $(EXECUTABLES)

.cpp:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o
	rm -f $(EXECUTABLES)
