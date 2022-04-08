CXX = g++

SOURCE_FILES := $(wildcard *.cpp)
OBJECT_FILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: main

%.o: %.cpp
	$(CXX) -c $*.cpp

main: $(OBJECT_FILES)
	$(CXX) $(OBJECT_FILES) -o main

clean:
	rm -f *.o main
