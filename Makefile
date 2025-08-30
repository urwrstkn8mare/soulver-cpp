all:
	cmake -GNinja -B build
	cmake --build build
.PHONY: all

install:
	cmake --install build
.PHONY: install

repl:
	c++ -std=c++23 ./examples/repl/repl.cpp -lsoulver-cpp -o examples/repl/repl
	./examples/repl/repl
.PHONY: repl

simple:
	c++ -std=c++23 ./examples/simple/simple.cpp -lsoulver-cpp -o examples/simple/simple
	./examples/simple/simple

clean:
	rm -rf build
.PHONY: clean

re: clean all
.PHONY: re
