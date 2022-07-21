fullprogram: program run

program:book.o movie.o music.o main.o
	g++ ./lib/book.o ./lib/movie.o ./lib/music.o  ./lib/main.o -o ./bin/program.exe

main.o:
	g++ -I "./include" -c ./src/main.cpp -o ./lib/main.o
	
entry.o:
	g++ -I "./include" -c ./src/entry.cpp -o ./lib/entry.o	
	
book.o:
	g++ -I "./include" -c ./src/book.cpp -o ./lib/book.o
	
movie.o:
	g++ -I "./include" -c ./src/movie.cpp -o ./lib/movie.o
	
music.o:
	g++ -I "./include" -c ./src/music.cpp -o ./lib/music.o
	
run:
	./bin/program.exe
