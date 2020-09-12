MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(dir $(MAKEFILE_PATH))
CPP_FILES := $(shell find src/ -type f -name '*.cpp')
CPP_FILENAMES := $(patsubst src/%.cpp,%,$(CPP_FILES))

define COMPILE_CPP

build/$(1).o : src/$(1).cpp
	@g++ -c src/$(1).cpp -I $(PROJECT_DIR)includes -I /d/MinGW_Dev/include/SDL2 -o build/$(1).o -O0 -std=c++17 -g

endef

$(foreach file, $(CPP_FILENAMES), $(eval $(call COMPILE_CPP,$(file))))

build/example1.o: examples/example1.cpp
	@g++ -c examples/example1.cpp -I $(PROJECT_DIR)includes -I /d/MinGW_Dev/include/SDL2 -o build/example1.o -O0 -std=c++17 -g

dist/example1: $(foreach file, $(CPP_FILENAMES), build/$(file).o) build/example1.o
	@g++ $(foreach file, $(CPP_FILENAMES), build/$(file).o) build/example1.o -L /d/MinGW_Dev/lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o dist/example1
