
target="$1"


res: main.c
	gcc $< -o $@


run: res
	./res ${target}

clean:
	rm -rf res*
