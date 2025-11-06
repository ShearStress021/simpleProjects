target="$1"
OS_NAME :=  $(shell uname -s)


ifeq ($(OS_NAME), Linux)
	RM := rm -rf 
else
	RM := del
endif

res: main.c
	gcc $< -o $@

run: res
	./res ${target} 

clean:
	$(RM) res*
