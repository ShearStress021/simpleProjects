
CFLAGS = -Wall -Wextra



ifeq ($(OS), Windows_NT)
	RM = del /Q
	RUN = res.exe
	PATH = $(subst /,\,$1)
	EXE = res.exe
else
	RM = rm -f
	RUN = ./res
	SLASH = /
	PATH = $1
	EXE = res
endif

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)



%.o: %.c
	gcc ${CFLAGS} -c $< -o $@


res: $(OBJS)
	gcc $^ -o $(EXE)


run: res
	$(RUN)



clean:
	$(RM) src\*.o res.*

.PHONY: clean run 
