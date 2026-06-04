cc = g++
CFLAGS = -Wall -Wextra -std=c++20 -pthread

BINDIR = bin

SERVER_DIR = $(BINDIR)/server
CLIENT_DIR = $(BINDIR)/client


.PHONY: all clean 


clean:
	rm -rf $(BINDIR) *.o *~


res: protocol.cpp client.cpp
	$(cc)  $^ -o  main


run: clean res
	./main


