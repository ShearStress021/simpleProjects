target ?= main.cpp


all: run

res:$(target)
	g++ --std=c++20 $< -o $@


run: clean res
	./res $(target)


clean:
	rm -rf res
