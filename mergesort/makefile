CC=g++
CFLAGS=-Wall -g -c
LDFLAGS=

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
EXECUTABLES := $(SOURCES:%.cpp=%)

all: $(EXECUTABLES)

$(EXECUTABLES): $(OBJECTS) 
	$(CC) $(LDFLAGS) $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(EXECUTABLES)
