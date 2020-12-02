dict: main.o link.o search.o write.o free.o readfile.o
	gcc -Wall -o dict main.o link.o search.o write.o free.o readfile.o
main.o: main.c link.h search.h write.h free.h readfile.h
	gcc -Wall -c main.c
link.o: link.c link.h
	gcc -Wall -c link.c
readfile.o: readfile.c readfile.h
	gcc -Wall -c readfile.c
search.o: search.c search.h
	gcc -Wall -c search.c
write.o: write.c write.h
	gcc -Wall -c write.c
free.o: free.c free.h
	gcc -Wall -c free.c

clean:
	rm *.o
	rm dict
