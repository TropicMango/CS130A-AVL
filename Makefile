CXXFLAGS = -std=c++11 -g -Wall -Wextra -Werror

.PHONY: clean tests

avl: avl.o Tree.o
	${CXX} $(CXXFLAGS) -o $@ $^

avl.o: avl.cpp Tree.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Tree.o: Tree.cpp Tree.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f avl avl.o Tree.o

test: avl
	@bash test.sh
