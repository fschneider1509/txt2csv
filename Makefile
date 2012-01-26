# Makefile for txt2csv
CC = /usr/bin/gcc
NAME = txt2csv
MAIN = main.c
FLAGS = -Wall -O2
CLEAN =

all: $(NAME)

$(NAME): $(MAIN)
	$(CC) $(FLAGS) $(MAIN) -o $(NAME)
	
clean:
	$(CLEAN)