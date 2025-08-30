all:
	cmake -GNinja -B build
	cmake --build build
.PHONY: all

install:
	cmake --install build
.PHONY: install

repl:
	c++ -std=c++23 ./examples/repl/repl.cpp -lSoulverWrapper -o examples/repl/repl
	./examples/repl/repl
.PHONY: repl

clean:
	rm -rf build
.PHONY: clean

re: clean all
.PHONY: re
