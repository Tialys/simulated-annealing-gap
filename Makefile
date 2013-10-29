# the compiler
CC = g++

#DEBUG = -g
DEBUG =
# Flags for linking
LFLAGS = -Wall $(DEBUG)
# Flags for compiling
CFLAGS = -Wall -c $(DEBUG)

# sources are all the .cpp files
SOURCES = $(shell ls *.cpp)
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

clean:
	rm -fr *.o *~

mrproper:
	rm -fr *.o *~ $(EXECUTABLE)
