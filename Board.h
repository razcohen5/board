#include <iostream>
#include <string>
#include <exception>
using namespace std;
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
	
	Bridge(Board *p,int a,int b);

	void operator=(char c);

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


	Bridge& operator[](pair<int,int> p);


	void operator=(char c);

	void deleteBoard();


	Board& operator=(const Board& other);



};


ostream& operator<< (ostream& os, const Board& b);





