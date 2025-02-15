CC = gcc

all:
	$(CC) -o editor *.c -lX11 -lclipboard -lm -lGL -lfreetype -lharfbuzz
