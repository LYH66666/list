OBJ=List.o
LIB=
STD=-std=gnu99
FLAG=-Wall -Werror
BIN=libList.a
CC=gcc

all:$(OBJ)
	ar -crv $(BIN) $(OBJ)

List.o:List.c List.h
	$(CC) $(STD) $(FLAG) -c $< -o $@

clean:
	rm $(BIN) $(OBJ)

.PHONY:all clean
	
