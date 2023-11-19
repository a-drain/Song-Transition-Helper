songs: driver.o song.o helpers.o
	g++ -o songs driver.o song.o helpers.o

driver.o: driver.cpp helpers.h
	g++ -c driver.cpp

helpers.o: helpers.h song.h
	g++ -c helpers.cpp

song.o: song.h
	g++ -c song.cpp

clean:
	rm *.o songs