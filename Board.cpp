#include <iostream>
#include <string>
#include <exception>
#include "Board.h"
using namespace std;

	Coordinate :: Coordinate(int a,int b){
		row=a;
		col=b;
	}
	
	Bridge :: Bridge(Board *p,int a,int b)
	{
		bp = p;
		i=a;
		j=b;
	}

	void Bridge :: operator=(char c)
	{
		if(c!='X'&&c!='O'&&c!='.')
			throw IllegalCharException(c);
		bp->b[i][j] = c;
		delete[] this;
	}

	bool Bridge :: operator==(char c) const
	{
		bool check = bp->b[i][j]==c;
		delete[] this;
		return check;
	}

	IllegalCharException :: IllegalCharException(char a)
	{
		c=a;
	}

	char IllegalCharException :: theChar() const
	{
		return c;
	}


	IllegalCoordinateException :: IllegalCoordinateException(int a, int b)
	{
		i = a;
		j = b;
	}

	string IllegalCoordinateException :: theCoordinate() const
	{
		string s = to_string(i) + "," + to_string(j);
		return s;
	}

	Board :: Board(int size)
	{
		this->size = size;
		char **t = new char* [size];
		for(int i=0;i<size;i++)
			t[i] = new char[size];

		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				t[i][j] = '.';

		b=t;
	}

	Board :: Board(const Board& other)
	{
		size = other.size;
		char **t = new char* [size];
		for(int i=0;i<size;i++)
			t[i] = new char[size];

		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				t[i][j] = other.b[i][j];
		b=t;
	}

	Bridge& Board :: operator[](const Coordinate& c)
	{
		Bridge *brp = nullptr;
		if(c.row<0||c.col<0||c.row>=size||c.col>=size)
			throw IllegalCoordinateException(c.row,c.col);
		else
			brp = new Bridge(this,c.row,c.col);
		return *brp;
	}

	void Board :: operator=(char c)
	{
		if(c!='X'&&c!='O'&&c!='.')
			throw IllegalCharException(c);
		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				b[i][j] = c;
	}

	void Board :: deleteBoard()
	{
		for(int i=0;i<size;i++)
			delete[] b[i];
		delete[] b;
	}

	Board& Board :: operator=(const Board& other)
	{
		deleteBoard();
		size = other.size;
		char **t = new char* [size];
		for(int i=0;i<size;i++)
			t[i] = new char[size];

		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				t[i][j] = other.b[i][j];
		b=t;
	}

	Board :: ~Board()
	{
		deleteBoard();
	}
	
ostream& operator<< (ostream& os, const Board& b){
    int i, j;
    for(i = 0; i < b.size; i++){
        for(j = 0; j < b.size; j++)
            os << b.b[i][j];
        os << endl;
    }
    return os;
}


int main() {
 	Board board1{4};  // Initializes a 4x4 board
	cout << board1 << endl;   // Shows an empty board:
/*	....
	....
	....
 	....  */ 
	board1[{1,1}]='X';
	board1[{1,2}]='O';
 	cout << board1 << endl;  // Shows the following board:
/*	....
 	.XO.
 	....
 	.... */
 	

 	try {
 		board1[{3,4}]='O';   // This should raise an exception
	} catch (const IllegalCoordinateException& ex) {
 		cout << "Illegal coordinate: " << ex.theCoordinate() << endl;  // prints "Illegal coordinate: 3,4"
 	}

 	board1 = '.';     // Fill the entire board with "."
	cout << board1 << endl;  /* Shows an empty board, as above */
 	try { 
 		board1 = 'a';        // This should raise an exception
 	} catch (const IllegalCharException& ex) {
 		cout << "Illegal char: " << ex.theChar() << endl;  // "Illegal char: a"
 	}

 	try {
 		board1[{0,1}] = 'x';  // This should raise an exception
 	} catch (const IllegalCharException& ex) {
 		cout << "Illegal char: " << ex.theChar() << endl;  // "Illegal char: x"
 	}

	Board board2 = board1;
 	board2[{0,0}] = 'X';
 	cout << board1 << endl;  /* Shows an empty board, as above */
 	cout << board2 << endl;  /* Shows a board with an X at top-left */

 	board1 = board2;
	board1[{3,3}] = 'O';
 	cout << board2 << endl;  /* Shows a board with an X at top-left */
 	cout << board1 << endl;  /* Shows a board with an X at top-left and O at bottom-right */

 	cout << "Good bye!" << endl;

 	return 0;
 }