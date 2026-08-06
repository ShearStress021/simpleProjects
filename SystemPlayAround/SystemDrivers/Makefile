
CC = g++

objects = main.o

%.o: %.cpp
	$(CC) -c $< -o $@

res: $(objects)
	$(CC) $< -o $@

run: clean res
	./res.exe


clean: 
	del *.0 *.exe
