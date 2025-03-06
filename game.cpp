#include "board.h"
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <thread>

static void testGame1();
static void testGame2();
static void testGame3();
static void testGame4();
static void twoPlayerGame();
char static ColCast(int col);
static pair<pair<int, int>, pair<int, int>> AskForMove();
static void PlayWithComputer();

static void RunTimeBenchmark();

int main()
{
	RunTimeBenchmark();
}

char static ColCast(int col)
{
	switch (col)
	{
	case 1:
		return 'A';
	case 2:
		return 'B';
	case 3:
		return 'C';
	case 4:
		return 'D';
	case 5:
		return 'E';
	case 6:
		return 'F';
	case 7:
		return 'G';
	case 8:
		return 'H';
	}
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
	pair<pair<pair<int, int>, pair<int, int>>, int> bestMove = theboard.findWhiteBestMove(4);
	cout << "best move is:" << bestMove.first.first.first << ColCast(bestMove.first.first.second) << "-->"<< bestMove.first.second.first << ColCast(bestMove.first.second.second) << endl;
	theboard.move(5, B, 4, C);
	theboard.printBoard();
	theboard.move(8, B, 6, C);
	theboard.printBoard();
	bestMove = theboard.findWhiteBestMove(4);
	cout << "best move is:" << bestMove.first.first.first << ColCast(bestMove.first.first.second) << "-->" << bestMove.first.second.first << ColCast(bestMove.first.second.second) << endl;
	theboard.move(4, C, 7, 6);
	theboard.printBoard();
	return;
}
static void testGame4()
{
	board theboard;
	theboard.printBoard();
	theboard.move(2, D, 4, D);
	theboard.printBoard();
	theboard.move(7, A, 6, A);
	theboard.printBoard();
	theboard.move(4, D, 5, D);
	theboard.printBoard();
	theboard.move(7, E, 5, E);
	theboard.printBoard();
	theboard.move(5, D, 6, E);
	theboard.printBoard();
	return;
}

static void twoPlayerGame()
{
	board theboard;
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
		pair<pair<int, int>, pair<int, int>> userMove = AskForMove();
		theboard.move(userMove.first.first, userMove.first.second, userMove.second.first, userMove.second.second);
		theboard.printBoard();
	}
	theboard.printBoard();
	return;
}


static pair<pair<int, int>, pair<int, int>> AskForMove()
{
	string piece;
	string target;
	int row;
	int col;
	int newRow;
	int newCol;
	bool moveIsLegal = false;
	cout <<"Enter the location of your piece and target (e.g. 2D 4D)" << endl;
	cin >> piece;
	cin >> target;
	try
	{
		if (isdigit(piece[0]))
		{
			row = piece[0] - '0';
			col = piece[1] - 'A' + 1;
			if (col > 8 || col < 0)
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
		if (row > 8 || row < 1 || col > 8 || col < 1 || newRow > 8 || newRow < 1 || newCol > 8 || newCol < 1)
		{
			throw "Invalid Move";
		}
		return { {row,col},{newRow,newCol} };
	}
	catch (...)
	{
		cout << "Invalid input, please try again" << endl;
		return AskForMove();
	}
}

static void PlayWithComputer()
{
	int depth;
	board theboard;
	theboard.PromptForUnicodeSupport();
	theboard.printBoard();
	cout << "Computer Smarterness: (Recommended is  4. If you set it to 5, it will take several minutes to compute in complex situation. Type 0 for dynamic depth, which will think 5 steps in simple situation and 4 steps in complex situation to keep compute time no more than a minute)" << endl;
	cin >> depth;
	cout << "You want to play: (B/W)" << endl;
	char user;
	cin >> user;
	if (user == 'W')
	{
		system("cls");
		theboard.printBoard();
		while (!theboard.isBlackCheckmated() && !theboard.isWhiteCheckmated())
		{
			if (theboard.mover == Black)
			{
				cout << "Computer is thinking..." << endl;
				using namespace std::chrono;
				duration<double> consume;
				high_resolution_clock::time_point begin;
				high_resolution_clock::time_point finish;
				begin = high_resolution_clock::now();
				pair<pair<pair<int, int>, pair<int, int>>, int> bestMove = theboard.findBlackBestMove(depth);
				finish = high_resolution_clock::now();
				consume += duration_cast<duration<double>>(finish - begin) ;
				cout << "After thinking for "<< consume.count() << " seconds, the computer plays : " << bestMove.first.first.first << ColCast(bestMove.first.first.second) << "-->" << bestMove.first.second.first << ColCast(bestMove.first.second.second) << endl;
				theboard.move(bestMove.first.first.first, bestMove.first.first.second, bestMove.first.second.first, bestMove.first.second.second);
				theboard.printBoard();
			}
			else
			{
				pair<pair<int, int>, pair<int, int>> userMove = AskForMove();
				system("cls");
				cout << "You play:" << userMove.first.first << ColCast(userMove.first.second) << "-->" << userMove.second.first << ColCast(userMove.second.second) << endl;
				if (!theboard.move(userMove.first.first, userMove.first.second, userMove.second.first, userMove.second.second))
				{
					userMove = AskForMove();
					theboard.move(userMove.first.first, userMove.first.second, userMove.second.first, userMove.second.second);
				}
				theboard.printBoard();
			}
		}
	}
	else
	{
		system("cls");
		while (!theboard.isBlackCheckmated() && !theboard.isWhiteCheckmated())
		{
			if (theboard.mover == White)
			{
				cout << "Computer is thinking..." << endl;
				using namespace std::chrono;
				duration<double> consume;
				high_resolution_clock::time_point begin;
				high_resolution_clock::time_point finish;
				begin = high_resolution_clock::now();
				pair<pair<pair<int, int>, pair<int, int>>, int> bestMove = theboard.findWhiteBestMove(depth);
				theboard.move(bestMove.first.first.first, bestMove.first.first.second, bestMove.first.second.first, bestMove.first.second.second);
				finish = high_resolution_clock::now();
				consume += duration_cast<duration<double>>(finish - begin);
				cout << "After thinking for " << consume.count() << " seconds, the computer plays : " << bestMove.first.first.first << ColCast(bestMove.first.first.second) << "-->" << bestMove.first.second.first << ColCast(bestMove.first.second.second) << endl;
				theboard.printBoard();
			}
			else
			{

				pair<pair<int, int>, pair<int, int>> userMove = AskForMove();
				system("cls");
				cout << "You play:" << userMove.first.first << ColCast(userMove.first.second) << "-->" << userMove.second.first << ColCast(userMove.second.second) << endl;
				if (!theboard.move(userMove.first.first, userMove.first.second, userMove.second.first, userMove.second.second))
				{
					userMove = AskForMove();
					theboard.move(userMove.first.first, userMove.first.second, userMove.second.first, userMove.second.second);
				}
				theboard.printBoard();
			}
		}
	}
	cout << "Game Over" << endl;
}
static void RunTimeBenchmark()
{
	using namespace std::chrono;
	duration<double> currrent1, currrent2, currrent3, currrent4;
	high_resolution_clock::time_point begin;
	high_resolution_clock::time_point finish;


	for (int i = 0; i < 4; i++)
	{
		cout << "Benchmarking for depth 4...("<< i+1<<"/4)" << endl;
		board testBoard;
		testBoard.move(2, D, 4, D);
		testBoard.move(7, D, 5, D);
		testBoard.move(1, B, 3, C);
		begin = high_resolution_clock::now();
		testBoard.findBlackBestMove(4);

		finish = high_resolution_clock::now();
		currrent1 += duration_cast<duration<double>>(finish - begin) / 4.0;


		testBoard.move(8, C, 6, E);

		begin = high_resolution_clock::now();
		testBoard.findWhiteBestMove(4);

		finish = high_resolution_clock::now();
		currrent2 += duration_cast<duration<double>>(finish - begin) / 4.0;


		testBoard.move(2, E, 4, E);
		testBoard.move(5, D, 4, E);
		testBoard.move(3, C, 4, E);
		testBoard.move(8, D, 5, D);
		testBoard.move(2, F, 3, F);
		testBoard.move(8, B, 6, C);
		testBoard.move(1, C, 3, E);
		testBoard.move(8, E, 8, C);
		testBoard.move(1, G, 2, E);
		testBoard.move(7, G, 6, G);
		begin = high_resolution_clock::now();
		testBoard.findWhiteBestMove(4);

		finish = high_resolution_clock::now();
		currrent3 += duration_cast<duration<double>>(finish - begin) / 4.0;
		testBoard.move(2, C, 3, C);


		begin = high_resolution_clock::now();
		testBoard.findBlackBestMove(4);
		finish = high_resolution_clock::now();
		currrent4 += duration_cast<duration<double>>(finish - begin) / 4.0;

		cout << "Waiting..." << endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	cout << "Benchmark Resutl:" << endl;
	cout << "Board1(B): " << currrent1.count() << "s" << endl;
	cout << "Board2(W): " << currrent2.count() << "s" << endl;
	cout << "Board3(W): " << currrent3.count() << "s" << endl;
	cout << "Board4(B): " << currrent4.count() << "s" << endl;
}