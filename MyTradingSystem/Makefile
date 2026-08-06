
CC = g++
PLATFORM ?= PLATFORM_DESKTOP


SRC ?= main.cpp market.cpp CSVReader.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRC))


%.o : %.cpp
	$(CC) -c $< -o $@


res: $(OBJS)
	$(CC) $(OBJS) -o $@


run: clean res
	./res


clean:
	del -rf *.o res*


.PHONY: all clean




