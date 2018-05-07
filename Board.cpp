#include <iostream>
#include <string>
#include <exception>
#include "Board.h"
using namespace std;


	
	Bridge :: Bridge(Board *p,int a,int b)
	{
		bp = p;
		i=a;
		j=b;
	}

	void Bridge :: operator=(char c)
	{
		if(c!='X'&&c!='O'&&c!='.')
		{
			const IllegalCharException *i = new IllegalCharException(c);
			throw *i;
		}
		bp->b[i][j] = c;
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

	Bridge& Board :: operator[](pair<int,int> p)
	{
		if(p.first<0||p.second<0||p.first>=size||p.second>=size)
		{
			const IllegalCoordinateException *i = new IllegalCoordinateException(p.first,p.second);
			throw *i;
		}	
		Bridge *brp = new Bridge(this,p.first,p.second);
		return *brp;
	}

	void Board :: operator=(char c)
	{
		if(c!='X'&&c!='O'&&c!='.')
		{
			const IllegalCharException *i = new IllegalCharException(c);
			throw *i;
		}
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


ostream& operator<< (ostream& os, const Board& b){
    int i, j;
    for(i = 0; i < b.size; i++){
        for(j = 0; j < b.size; j++)
            os << b.b[i][j];
        os << endl;
    }
    return os;
}


// int main() {
// 	Board board1{4};  // Initializes a 4x4 board
// 	cout << board1 << endl;   /* Shows an empty board:
// 	....
// 	....
// 	....
// 	....
// 	*/
// 	board1[{1,1}]='X';
// 	board1[{1,2}]='O';
// 	cout << board1 << endl;  /* Shows the following board:
// 	....
// 	.XO.
// 	....
// 	....
// 	*/

// 	try {
// 		board1[{3,4}]='O';   // This should raise an exception
// 	} catch (const IllegalCoordinateException& ex) {
// 		cout << "Illegal coordinate: " << ex.theCoordinate() << endl;  // prints "Illegal coordinate: 3,4"
// 	}

// 	board1 = '.';     // Fill the entire board with "."
// 	cout << board1 << endl;  /* Shows an empty board, as above */
// 	try { 
// 		board1 = 'a';        // This should raise an exception
// 	} catch (const IllegalCharException& ex) {
// 		cout << "Illegal char: " << ex.theChar() << endl;  // "Illegal char: a"
// 	}

// 	try {
// 		board1[{0,1}] = 'x';  // This should raise an exception
// 	} catch (const IllegalCharException& ex) {
// 		cout << "Illegal char: " << ex.theChar() << endl;  // "Illegal char: x"
// 	}

// 	Board board2 = board1;
// 	board2[{0,0}] = 'X';
// 	cout << board1 << endl;  /* Shows an empty board, as above */
// 	cout << board2 << endl;  /* Shows a board with an X at top-left */

// 	board1 = board2;
// 	board1[{3,3}] = 'O';
// 	cout << board2 << endl;  /* Shows a board with an X at top-left */
// 	cout << board1 << endl;  /* Shows a board with an X at top-left and O at bottom-right */

// 	cout << "Good bye!" << endl;

// 	return 0;
// }
