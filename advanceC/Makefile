target ?= main.cpp


res: $(target)
	gcc $< -o $@


run: clean res
	./res


clean:
	rm -rf res
