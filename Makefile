###########################################################
#
# Name: Alex Gonzalez, Pierre Kharat
# User: cssc0816, cssc0844
# Class: CS 570, Summer 2019
# Assignment 3, EMP
# Filename: Makefile
#
###########################################################
EXEC = emp
FILES = a3.c
CC = gcc
LFLAGS = -g
CFLAGS = -g -c -I.
OBJECTS = $(FILES:.c=.o)
$(EXEC):$(OBJECTS)
        $(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
        rm -f *.o
.c.o:
        $(CC) $(CFLAGS) $<
clean:
        rm -f *.o $(EXEC)
#######################[ EOF: Makefile ]###################
