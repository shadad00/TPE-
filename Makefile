#
# Makefile para el TP Final de Programacion Imperativa
#

#Compilador
CC = gcc

# Flags para el compilador gcc
# -g
# -Wall
# -pedantic -std=c99
#  -fsanitize=address
CFLAGS = -g -Wall -pedantic -std=c99 -fsanitize=address -g

#Archivos a utilizar
# SOURCES = Archivos .c
# OBJETCS = Archivos .o
# TARGET = archivo output
SOURCES = 
OBJECTS = $(SOURCES:.c=.o)
TARGET =

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
