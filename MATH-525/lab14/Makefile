CC = gcc
FFLAGS = -O3 -Wall -std=c99
LFFLAG =
OBJECTS = PowerIterationAlgorithm.o \
matrix.o

.PHONY: clean

PI.exe: $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o PI.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<

clean:
		del -f $(OBJECTS) PI.exe
