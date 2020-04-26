# makefile for copy a directories
CC=gcc
CFLAGS=-c
OFLAGS=-o
FFLAGS=-f
RM=rm
copiere: copiereDir.o
	$(CC) copiereDir.o $(OFLAGS) copiere
copiereDir.o: copiereDir.c
	$(CC) $(CFLAGS) copiereDir.c
clean: 
	$(RM) $(FFLAGS) *.o
