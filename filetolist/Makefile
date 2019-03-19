CC = gcc
CFLAGS = -Wall -pedantic -g
LDFLAGS = -L.

all :
	@echo "Compiling"
	$(CC) $(CFLAGS) libList.c -c -o libList.o
	ar rvs libList.a libList.o
	$(CC) $(CFLAGS) filetolist.c $(LDFLAGS) -lList -o filetolist

clean :
	rm -f filetolist libList.a libList.o