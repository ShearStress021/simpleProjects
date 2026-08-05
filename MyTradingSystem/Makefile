
CC = g++
PLATFORM ?= PLATFORM_DESKTOP


SRC ?= main.cpp market.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRC))


%.o : %.cpp
	$(CC) -c $< -o $@


res: $(OBJS)
	$(CC) $(OBJS) -o $@


run: clean res
	./res


clean:
	rm -rf *.o res*


.PHONY: all clean




