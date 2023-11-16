songs: driver.o song.o
	g++ -o songs driver.o song.o

driver.o: driver.cpp song.h
	g++ -c driver.cpp

song.o: song.h
	g++ -c song.cpp

clean:
	rm *.o songs