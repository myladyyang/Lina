SRC:=$(wildcard *cpp)
OBJ:=$(SRC:.cpp=.o)
CXX=clang++
CXXFLAGS=-Iinclude -std=c++11 
LDFLAGS=-pthread -lboost_system

.PHONY: utils

all: lina utils
	echo "lina created"

lina: ${OBJ}
	${CXX} -o $@ $+ ${LDFLAGS}


utils: 
	make utils/makefile

clean:
	rm *o lina
