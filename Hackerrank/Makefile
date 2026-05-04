target="$1"



res: $(target)
	g++ --std=c++23 $< -o $@


run: res
	./res


clean:
	rm -rf res
