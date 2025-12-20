
CXX = gcc

TARGETS = res

SRCS =  main.cpp

objects = $(SRCS:.cpp=.o)


$(TARGETS): $(objects)
	g++ $(objects) -o $(TARGETS) -lraylib


run: $(TARGETS)
	./$(TARGETS)


clean:
	rm -rf $(TARGETS) $(objects)
