# Makefile

# Compiler
CXX = g++
CC = gcc

# Compiler flags
FLAGS = -g -Wall

# Different C++ versions
pointer_arithmetics_cpp23.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++23 $(FLAGS) $^ -o $@

pointer_arithmetics_cpp20.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++20 $(FLAGS) $^ -o $@

pointer_arithmetics_cpp17.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++17 $(FLAGS) -g $^ -o $@
  
pointer_arithmetics_cpp14.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++14 $(FLAGS) -g $^ -o $@
  
pointer_arithmetics_cpp11.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++11 $(FLAGS) -g $^ -o $@
  
pointer_arithmetics_cpp03.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++03 $(FLAGS) -g $^ -o $@
  
pointer_arithmetics_cpp98.exe: pointer_arithmetics.cpp
	$(CXX) --std=c++98 $(FLAGS) -g $^ -o $@

# Different C versions
pointer_arithmetics_c23.exe: pointer_arithmetics.c
	$(CC) --std=c23 $(FLAGS) $^ -o $@
  
pointer_arithmetics_c17.exe: pointer_arithmetics.c
	$(CC) --std=c17 $(FLAGS) $^ -o $@
  
pointer_arithmetics_c11.exe: pointer_arithmetics.c
	$(CC) --std=c11 $(FLAGS) $^ -o $@

pointer_arithmetics_c99.exe: pointer_arithmetics.c
	$(CC) --std=c99 $(FLAGS) $^ -o $@
  
pointer_arithmetics_c90.exe: pointer_arithmetics.c
	$(CC) --std=c90 $(FLAGS) $^ -o $@
  
pointer_arithmetics_c89.exe: pointer_arithmetics.c
	$(CC) --std=c89 $(FLAGS) $^ -o $@

pointer_arithmetics.c: pointer_arithmetics.cpp
	cp $^ $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump *.c