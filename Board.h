#include <iostream>
#include <string>
#include <exception>
using namespace std;
class Coordinate;
class Bridge;
class IllegalCharException;
class IllegalCoordinateException;
class Board;
class Bridge
{
public:

	Board *bp;
	int i;
	int j;
	
	Bridge(Board *p,const int a,const int b);

	Bridge(const Bridge& other);

	void operator=(char c);

	bool operator==(char c) const;

};

class IllegalCharException : public exception 
{
public:

	char c;

	IllegalCharException(char a);


	char theChar() const;

};

class IllegalCoordinateException : public exception 
{
public:

	int i;
	int j;

	IllegalCoordinateException(int a, int b);


	string theCoordinate() const;

};

class Board
{
public:
	int size;
	char **b;

	Board(int size);

	Board(const Board& other);


	Bridge operator[](const Coordinate& c);


	void operator=(char c);

	void deleteBoard();


	Board& operator=(const Board& other);

	~Board();

};

class Coordinate{
public:
    int row,col;

    Coordinate(int a,int b);


};



ostream& operator<< (ostream& os, const Board& b);