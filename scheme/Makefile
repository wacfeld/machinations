CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second
EXEC = $(shell basename $(CURDIR)).out
LIBS = 
OBJECTS = main.o lexer.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} ${LIBS} ../bin/regex.a
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

