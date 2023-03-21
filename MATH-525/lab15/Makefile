CC = gcc
FFLAGS = -O3 -Wall -std=c99
LFFLAG =
OBJECTS = Hessenberg.o \
trimatrix.o \
QRdecomp.o \
FindZero.o \
GetShift.o \
QRA.o \
matrix.o \
main.o \

.PHONY: clean

main.exe: $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<

clean:
		del -f $(OBJECTS) main.exe
