target ?= main.cpp


all: run

res:$(target)
	g++ --std=c++23 $< -o build/$@ -lstdc++exp
run: clean res
	.build/res 
clean:
	del \Q build\res*

.PHONY: all res clean
