SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra 


%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

	
res.exe: $(OBJS)
	gcc $< -o $@

run: clean res.exe
	res.exe

clean: 
	del /Q src\*.o res*
