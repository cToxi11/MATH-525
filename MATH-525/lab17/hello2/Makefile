C = gcc

FFLAGS = -Wall -std=c99 -Xpreprocessor -fopenmp
LFLAGS = -lgomp

OBJECTS = omp_hello.o

main.exe: $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<

clean:
		rm -f $(OBJECTS) *.exe