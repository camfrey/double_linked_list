CC=g++
CFLAGS=-I.
DEPS = DLL.hpp Coder.hpp DNode.hpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: DLL.o Coder.o DNode.o
	$(CC) -o lab4 MainDLL.cpp DLL.o Coder.o DNode.o

clean:
	rm lab4
	rm -f ./*.o