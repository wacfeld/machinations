CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second
EXEC = $(shell basename $(CURDIR))
LIBS = 
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

