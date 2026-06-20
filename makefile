
CC = gcc
CFLAGS = -Wall -Wextra -g
EXEC = pontos
 
OBJS = main.o geometria.o heap.o lista.o no.o
 
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
 
geometria.o: geometria.c geometria.h
	$(CC) $(CFLAGS) -c geometria.c
 
heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c
 
lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c
 
no.o: no.c no.h
	$(CC) $(CFLAGS) -c no.c
 
clean:
	rm -f $(OBJS) $(EXEC)