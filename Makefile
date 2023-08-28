tests: 
	g++ -o tests cpu.cpp tests.cpp
	./tests

clean:
	rm tests

.PHONY: tests
