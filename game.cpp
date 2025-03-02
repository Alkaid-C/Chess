#include "board.h"
#include <iostream>


int main()
{
	board theboard;
	theboard.printBoard();
	cout << "tomove" << endl;
	theboard.move(2, E, 4, E);
	theboard.printBoard();
	theboard.move(7, D, 5, D);
	theboard.printBoard();
	theboard.move(2, F, 3, F);
	theboard.printBoard();
	theboard.move(5, D, 4, E);
	theboard.printBoard();
	theboard.move(3, F, 4, E);
	theboard.printBoard();
	theboard.move(8, B, 6, C);
	theboard.printBoard();
	theboard.move(1, G, 3, F);
	theboard.printBoard();
	theboard.move(8, C, 6, E);
	theboard.printBoard();
	theboard.move(2, B, 3, B);
	theboard.printBoard();
	theboard.move(8, D, 6, D);
	theboard.printBoard();
	theboard.move(1, C, 2, B);
	theboard.printBoard();
	theboard.move(8, E, 8, C);
	theboard.printBoard();
	theboard.move(2, B, 1, C);
	theboard.printBoard();
	theboard.move(8, G, 6, F);
	theboard.printBoard();
	theboard.move(2, D, 3, D);
	theboard.printBoard();
	theboard.move(7, G, 6, G);
	theboard.printBoard();
	theboard.move(1, F, 2, E);
	theboard.printBoard();
	theboard.move(6, C, 4, D);
	theboard.printBoard();
	theboard.move(2, A, 3, A);
	theboard.printBoard();
	theboard.move(6, F, 4, G);
	theboard.printBoard();
	theboard.move(2, H, 3, H);
	theboard.printBoard();
	theboard.move(4, G, 3, E);
	theboard.printBoard();
	theboard.move(1, D, 2, D);
	theboard.printBoard();
	theboard.move(6, D, 3, G);
	theboard.printBoard();
	return 0;
}