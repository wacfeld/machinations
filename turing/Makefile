CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second
# EXEC = $(shell basename $(CURDIR))
LIBS = 
OBJECTS = main.o tape.o table.o instr.o turing.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = $(shell basename $(CURDIR)).out
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

