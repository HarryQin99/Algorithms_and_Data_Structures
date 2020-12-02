all: map1 map2
map1: main.o link_2.o readfile.o tree.o search.o write.o main2.o
	gcc -Wall -o map1 main.o link_2.o readfile.o tree.o  search.o write.o -lm
map2: main2.o link_2.o readfile.o tree.o search.o write.o main2.o
	gcc -Wall -o map2 main2.o link_2.o readfile.o tree.o search.o write.o -lm
main.o: main.c link_2.h readfile.h tree.h search.h write.h
	gcc -Wall -c main.c
main2.o: main2.c link_2.h readfile.h tree.h search.h write.h
	gcc -Wall -c main2.c
readfile.o: readfile.c readfile.h
	gcc -Wall -c readfile.c
link_2.o: link_2.c link_2.h 
	gcc -Wall -c link_2.c
tree.o: tree.c tree.h
	gcc -Wall -c tree.c
search.o: search.c search.h readfile.h link_2.h tree.h
	gcc -Wall -c search.c
write.o: write.c write.h link_2.h search.h
	gcc -Wall -c write.c




clean:
	rm *.o
	rm map2
	rm map1
	
