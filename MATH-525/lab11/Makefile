# $ISUHPC/lectures/lecture11/codes/linked_list/Makefile
CC = gcc
FFLAGS = -O3 -Wall
LFFLAG =
OBJECTS = main.o \
GetNumberOfLetters.o \
GenerateList.o \
Print.o \
GetKey.o \
SearchList.o \
DeleteList.o

.PHONY: clean help

main.exe: $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
		$(CC) $(FFLAGS) -c $<

clean:
		del -f $(OBJECTS) main.exe
help:
		@echo "Valid targets:"
		@echo " main.exe"
		@echo " main.o"
		@echo " GetNumberOfLetters.o"
		@echo " GenerateList.o"
		@echo " Print.o"
		@echo " GetKey.o"
		@echo " SearchList.o"
		@echo " DeleteList.o"
		@echo " clean: removes *.o and *.exe files"
