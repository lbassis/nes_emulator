tests: 
	g++ -o tests/tests cpu_registers.cpp cpu_memory.cpp cpu_general.cpp tests/tests.cpp
	./tests/tests

verbose_tests:
	g++ -o tests/tests cpu_registers.cpp cpu_memory.cpp cpu_general.cpp tests/tests.cpp -DVERBOSE
	./tests/tests

clean:
	rm ./tests/tests

.PHONY: tests verbose_tests
