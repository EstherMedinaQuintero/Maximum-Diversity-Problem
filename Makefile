# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# @author Esther M. Quintero

CXX = g++						        # The C++ compiler command
CXXFLAGS = -std=c++17 -Wall -I./include -I./src -O3	 # The C++ compiler options (C++17, warn all, optimize)
LDFLAGS =						        # The linker options (if any)

# Debug C++ compiler options
DEBUG_CXXFLAGS = -g -DDEBUG

# List of source files
SRCS = ./src/algorithm.cc \
       ./src/branch.cc \
       ./src/grasp.cc \
       ./src/greedy.cc \
       ./src/local-search.cc \
       ./src/point.cc \
       ./src/problem.cc \
       ./src/solution.cc \
       ./src/tabu-search.cc \
       ./src/utilities.cc \
       ./main.cc

# Generate the object file names by replacing .cc with .o
OBJS = $(patsubst ./src/%.cc, ./build/%.o, $(SRCS))

# The all target builds the program.
all: mdp

mdp: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Indicate that the all and clean targets do not correspond to actual files.
.PHONY: all clean

# Rules to build object files
./build/%.o: ./src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build with debug flags
debug: CXXFLAGS += $(DEBUG_CXXFLAGS)
debug: clean all

# The clean target removes all of the executable files and object files produced by the build process.
# We can use it for additional housekeeping purposes.
clean :
	rm -f mdp
	rm -f ./build/*.o
	rm -rf a.out
	find . -name '*~' -exec rm {} \;