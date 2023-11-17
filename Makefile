CC = g++

final: vgcserver.o 
	$(CC) vgcserver.o -o vgcserver

main.o: vgcserver.cpp
	$(CC) -c vgcserver.cpp

clean:
	rm *.o vgcserver
