SRC = main.cpp memoryChecker.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRC))

%.o: %.cpp
	g++ -c $< -o $@



res : $(OBJS)
	g++ $(OBJS) -o $@


run: clean res
	./res


clean:
	del res*


PHONY: clean res run
