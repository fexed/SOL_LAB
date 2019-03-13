all :
	@echo "Compiling"
	gcc -std=c99 -Wall libList.c -c -o libList.o
	ar rvs libList.a libList.o
	gcc -Wall -pedantic -g filetolist.c -L. -lList -o filetolist

clean :
	rm -f filetolist libList.a libList.o