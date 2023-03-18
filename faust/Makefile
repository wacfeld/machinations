CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second
EXEC = $(shell basename $(CURDIR)).out
LIBS = 
OBJECTS = main.o instr.o table.o regex.o io.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} ${LIBS}
	cp ${OBJECTS} ${EXEC} ../bin
	ar rcs ../bin/regex.a ../bin/*.o
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

