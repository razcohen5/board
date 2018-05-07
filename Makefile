CCX=gcc -std=c++11

a.out: Board.o
		$(CCX) main.cpp *.o
		
Board.o: Board.cpp Board.h
		$(CCX) -c Board.cpp
		
Clean:
		rm *.o a.out