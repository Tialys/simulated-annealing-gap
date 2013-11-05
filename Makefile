# the compiler
CC = g++

#DEBUG = -g
DEBUG =
# Flags for linking
LFLAGS = -Wall -std=c++11 $(DEBUG)
# Flags for compiling
CFLAGS = -Wall -std=c++11 -c $(DEBUG)

SRC= src
# sources are all the .cpp files
SOURCES = $(shell ls $(SRC)/*.cpp)
# objects are the respective .o files
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = test

# make the executable
all: $(EXECUTABLE)

# make executable from objects
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# generate each .o from each .cpp 
# $@: target (here a .o)
# $<: first dependency (here, only one, a .cpp)
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

task: src/task.cpp
	$(CC) $(CFLAGS) $< -o src/$@.o

agent: src/agent.cpp
	$(CC) $(CFLAGS) $< -o src/$@.o

instance: src/instance.cpp
	$(CC) $(CFLAGS) $< -o src/$@.o

clean:
	rm -fr $(SRC)/*.o $(SRC)/*~

mrproper:
	rm -fr $(SRC)/*.o $(SRC)/*~ $(EXECUTABLE)
