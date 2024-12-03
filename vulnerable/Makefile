.PHONY: all clean
LDFLAGS =
CXXFLAGS = -Wall
CXX = g++

all: taskManager

taskManager: taskManager.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean: Makefile 
	rm -f taskManager
	rm -f *~

