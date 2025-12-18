CXX = g++

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = res

SRCS = main.cpp 

objects = $(SRCS:.cpp=.o)

$(TARGET): $(objects)
	$(CXX) $(objects) -o $(TARGET) $(LIBS)



run: $(TARGET)
	./$(TARGET)


clean:
	rm -rf $(TARGET) $(objects)
