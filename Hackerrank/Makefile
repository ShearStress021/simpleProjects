target ?= main.cpp

res: $(target)
	g++ --std=c++23 $< -o $@


run: clean res
	./res


clean:
	del -rf res
