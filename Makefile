CXX=g++
CC=gcc
OUT_DIR=bin
OUT_NAME=BrainFuck
OBJECT_DIR=obj
SOURCE_DIR=src
FLAGS=-Wall

# Build command
build: obj/BIS.o
	@echo Compiling Brainfuck Interpreter Shell
	$(CXX) -o $(OUT_DIR)/$(OUT_NAME) obj/BIS.o

# Object compile
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@


# PHONY
.PHONY: fullclean clean
fullclean: clean
	rm -rf $(OUT_DIR)

clean:
	rm obj/*
