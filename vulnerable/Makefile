.PHONY: all clean cleanLogs
LDFLAGS =
CXXFLAGS = -Wall
CXX = g++

 all: logger
# all: taskManager taskManagerDebug basicHeap

logger: logger.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean: Makefile 
	rm -f taskManager
	rm -f taskManagerDebug
	rm -f basicHeap
	rm -f logger
	rm -f *~

cleanLogs: Makefile
	rm -f LOG_FILE_*
