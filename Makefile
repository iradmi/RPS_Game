#!/bin/make

SHELL = /bin/sh

SRC_DIR := src
INC_DIR := include
OUT_DIR := build

EXE := $(OUT_DIR)/game
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(SRC))

CPPFLAGS := -O3 -Wall -Wextra -pedantic -std=c++20
CPPFLAGS += -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align
CPPFLAGS += -Wstrict-overflow=5 -Wwrite-strings
CPPFLAGS += -Wcast-qual -Wswitch-default -Wswitch-enum 
CPPFLAGS += -Wconversion -Wunreachable-code -Weffc++
LDFLAGS  := 
LDLIBS   := 

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(OUT_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) -I$(INC_DIR) $(CPPFLAGS) -c $< -o $@  

clean:
	@$(RM) $(OUT_DIR)/*

-include $(OBJ:.o=.d)

run: 
	$(EXE)
	
