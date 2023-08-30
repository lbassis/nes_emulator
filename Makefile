tests: 
	g++ -o tests cpu_registers.cpp cpu_memory.cpp cpu_general.cpp tests.cpp
	./tests

clean:
	rm tests

.PHONY: tests
