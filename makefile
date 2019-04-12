all: bb.x
CPPFLAGS=-std=c++11 -lpthread
LDFLAGS=-lpthread

bb.x: main.o BoundedBuffer.o
	g++ -o $@ $^ $(LDFLAGS)

main.o: main.cpp BoundedBuffer.hpp
	g++ -c -o $@ $< $(CPPFLAGS)

BoundedBuffer.o: BoundedBuffer.cpp BoundedBuffer.hpp
	g++ -c -o $@ $< $(CPPFLAGS)

clean:
	rm -f *.x *.o *~
