CC = mpicc
FFLAGS = -O3 -Wall -std=c99
LFLAGS = -lm
OBJECTS = main.o matrix.o

main.exe: $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<s

clean :
		rm -f $(OBJECTS) *.exe
