all:
	g++ -c tinyxml/*.cpp
	g++ tinystr.o tinyxmlparser.o tinyxmlerror.o tinyxml.o -o trabalhocg main.cpp arena.cpp circle.cpp player.cpp bullet.cpp -lGL -lglut

clean:
	rm *.o trabalhocg
