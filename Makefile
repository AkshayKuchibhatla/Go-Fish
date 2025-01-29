CC=g++
STD=c++17

# Link the object files with ncurses for the main program
build/main: build/main.o build/Card.o build/GoFish.o build/GFPlayer.o
	# This uses special variables to avoid retyping all the requirements
	$(CC) -g -O0 -o $@ $^ -std=$(STD) -lncursesw 

# Link the object files with ncurses for the test program
build/test: build/tests.o build/Card.o build/GoFish.o build/GFPlayer.o
	$(CC) -g -O0 -o $@ $^ -std=$(STD) -lncursesw

# Build a single c++ source file
build/%.o: src/%.cpp
	# Create the output directory if needed
	@mkdir -p build
	# Tell the compiler to figure out what the source file depends on so that make on rebuilds what is needed
	@$(CC) -MM -MT $@ $< > build/$*.d
	# Actually compile the file
	$(CC) -g -O0 -c -o $@ $< -std=$(STD)

# Include all the extra info the compiler created
-include build/*.d

# Tell make that the following should always be run
.PHONY: test all clean

test: build/test
	./build/test

all: build/test build/main

clean:
	rm -rf build
