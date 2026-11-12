target ?= main.cpp

U_NAME := $(shell uname -s)


ifeq ($(U_NAME), Linux)
	MKDIR := mkdir
	RM := rm -rf 
	EXE := ./build/res
else
	MKDIR := mkdir
	RM := del /Q
	EXE := build\res.exe
endif
all: run

res:$(target)
	$(MKDIR) build
	g++ --std=c++23 $< -o build/res -lstdc++exp
run: clean res
	$(EXE)
clean:
	$(RM) build

.PHONY: all res clean

