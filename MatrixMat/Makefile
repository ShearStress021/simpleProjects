
CFLAGS = -Wall -Wextra


ifeq ($(OS), Windows_NT)
	RM = del /Q
	RUN = res.exe
	OBJS_PATH = src\*.o 
	EXE = .exe
else
	RM = rm -f
	RUN = ./res
	SLASH = /
	OBJS_PATH = src/*.o 
	EXE = 
endif

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
TARGET = res$(EXE)


all: $(TARGET)


%.o: %.c
	gcc ${CFLAGS} -c $< -o $@


$(TARGET): $(OBJS)
	gcc $^ -o $@


run: clean $(TARGET) 
	$(RUN)	



clean:
	$(RM) $(OBJS_PATH) res*

.PHONY: clean run 
