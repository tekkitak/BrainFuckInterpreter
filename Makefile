CXX=g++
CC=gcc
OUT_EXE_NAME=BrainFuck
OBJECT_DIR=obj
SOURCE_DIR=src
FLAGS=-Wall

# Build command
build: obj/BIS.o
	@echo Compiling Brainfuck Interpreter Shell
	$(CXX) -o $(OUT_EXE_NAME) obj/BIS.o

# Object compile
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@


# PHONY
.PHONY: fullclean clean
fullclean: clean
	rm $(OUT_EXE_NAME).exe

clean:
	rm obj/*
