#include "board.h"
#include <iostream>

static void testGame1();
static void testGame2();
static void testGame3();
static void twoPlayerGame();

int main()
{
	twoPlayerGame();
}
static void testGame1()
{
	board theboard;
	theboard.printBoard();
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
	return ;
}

static void testGame2()
{
	board theboard;
	theboard.printBoard();
	theboard.move(2, D, 4, D);
	theboard.printBoard();
	theboard.move(7, D, 5, D);
	theboard.printBoard();
	theboard.move(1, G, 3, F);
	theboard.printBoard();
	theboard.move(8, C, 5, F);
	theboard.printBoard();
	theboard.move(2, E, 3, E);
	theboard.printBoard();
	theboard.move(8, B, 6, C);
	theboard.printBoard();
	theboard.move(1, F, 3, D);
	theboard.printBoard();
	theboard.move(5, F, 3, D);
	theboard.printBoard();
	theboard.move(2, C, 3, D);
	theboard.printBoard();
	theboard.move(8, D, 6, D);
	theboard.printBoard();
	theboard.move(1, C, 2, D);
	theboard.printBoard();
	theboard.move(8, E, 8, C);
	theboard.printBoard();
	theboard.move(2, B, 4, B);
	theboard.printBoard();
	theboard.move(6, D, 6, G);
	theboard.printBoard();
	theboard.move(3, F, 4, H);
	theboard.printBoard();
	theboard.move(6, G, 3, D);
	theboard.printBoard();
	theboard.move(4, H, 3, F);
	theboard.printBoard();
	theboard.move(7, E, 6, E);
	theboard.printBoard();
	theboard.move(1, D, 2, E);
	theboard.printBoard();
	theboard.move(3, D, 6, G);
	theboard.printBoard();
	theboard.move(1, E, 1, G);
	theboard.printBoard();
	theboard.move(8, F, 6, D);
	theboard.printBoard();
	theboard.move(3, F, 4, H);
	theboard.printBoard();
	theboard.move(6, G, 4, E);
	theboard.printBoard();
	theboard.move(2, E, 3, F);
	theboard.printBoard();
	theboard.move(4, E, 4, H);
	theboard.printBoard();
	theboard.move(3, F, 7, F);
	theboard.printBoard();
	theboard.move(4, H, 2, H);
	theboard.printBoard();
	return;
}

static void testGame3()
{
	board theboard;
	theboard.printBoard();
	theboard.move(2, E, 4, E);
	theboard.printBoard();
	theboard.move(7, D, 5, D);
	theboard.printBoard();
	theboard.move(1, D, 5, H);
	theboard.printBoard();
	theboard.move(5, D, 4, E);
	theboard.printBoard();
	theboard.move(1, F, 5, B);
	theboard.printBoard();
	theboard.move(8, C, 7, D);
	theboard.printBoard();
	theboard.move(5, B, 4, C);
	theboard.printBoard();
	theboard.move(8, B, 6, C);
	theboard.printBoard();
	theboard.move(5, H, 7, F);
	theboard.printBoard();
	return;
}

static void twoPlayerGame()
{
	board theboard;
	string piece;
	string target;
	int row;
	int col;
	int newRow;
	int newCol;
	theboard.printBoard();
	while (!theboard.isBlackCheckmated() && !theboard.isWhiteCheckmated())
	{
		if (theboard.mover == White)
		{
			cout << "White's turn" << endl;
		}
		else
		{
			cout << "Black's turn" << endl;
		}
		cout << "Enter row and col of the piece you want to move (e.g., 2d, 2D, d2, or D2)" << endl;
		cin >> piece;
		cout << "Enter row and col of the square you want to move to(e.g., 4d, 4D, d4, or D4)" << endl;
		cin >>target;
		if (isdigit(piece[0]))
		{
			row = piece[0] - '0';
			col = piece[1] - 'A'+1;
			if (col > 8 || col <0)
			{
				col = piece[1] - 'a' + 1;
			}
		}
		else
		{
			row = piece[1] - '0';
			col = piece[0] - 'A' + 1;
			if (col > 8 || col < 0)
			{
				col = piece[0] - 'a' + 1;
			}
		}
		if (isdigit(target[0]))
		{
			newRow = target[0] - '0';
			newCol = target[1] - 'A' + 1;
			if (newCol > 8 || newCol < 0)
			{
				newCol = target[1] - 'a' + 1;
			}
		}
		else
		{
			newRow = target[1] - '0';
			newCol = target[0] - 'A' + 1;
			if (newCol > 8 || newCol < 0)
			{
				newCol = target[0] - 'a' + 1;
			}
		}
		theboard.move(row, col, newRow, newCol);
		theboard.printBoard();
	}
	theboard.printBoard();
	return;
}
