# Makefile for Linux

CC = gcc 
DEST = /usr/local/bin
LDFLAGS = -L/usr/local/lib
SRC = mqercmp.c
OBJ = mqercmp.o
EXE = mqercmp

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

$(OBJ): $(SRC)

clean:
	rm -f $(OBJ) *~ $(EXE)	

install: $(EXE)
	install -s $(EXE) $(DEST)
