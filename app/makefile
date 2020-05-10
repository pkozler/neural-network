CC = gcc
CFLAGS = -Wall -pedantic -ansi
BIN = neural_net
OBJ = main.o neuron.o edge.o load.o classify.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ -lm

