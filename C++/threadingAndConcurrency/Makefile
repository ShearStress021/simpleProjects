target ?= main.cpp


res: $(target)
	g++ $< -o $@

run: clean res
	./res


clean:
	rm -rf res
