CPP=g++
CPPFLAGS=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -std=c++11 -g -O2

BIN_DIR=bin

all: $(BIN_DIR)/main $(BIN_DIR)/gen

$(BIN_DIR)/main: main.cpp **/*.cpp Makefile
	$(CPP) $(CPPFLAGS) -o $@ main.cpp

$(BIN_DIR)/gen: sampleGenerator.cpp Makefile
	$(CPP) $(CPPFLAGS) -o $@ sampleGenerator.cpp
