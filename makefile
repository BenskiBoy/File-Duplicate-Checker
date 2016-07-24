DEBUG = 0
ifeq ($(DEBUG), 1)
	CFLAGS =-DDEBUG
else
	CFLAGS =-DNDEBUG
endif

CXX = g++ $(CFLAGS)

all: fileDuplicateChecker

fileDuplicateChecker: fileDuplicateChecker.cpp
	$(CXX) -Wall -g fileDuplicateChecker.cpp -o fileDuplicateChecker 