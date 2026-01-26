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
static void PlayWithComputer();
static void RunTimeBenchmark(int depth, int round);
char static ColCast(int col);
static pair<Loc, Loc> AskForMove();
string encodeLoc(Loc loc);
bool PromptForUnicodeSupport();

int main()
{
	cout << "Do you want to..." << endl;
	cout << "1) play two player game" << endl;
	cout << "2) play with computer" << endl;
	cout << "3) Run Benchmark" << endl;
	cout << "type 1 or 2 or 3 to begin." << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		twoPlayerGame();
	}
	if (choice == 2)
	{
		PlayWithComputer();
	}
	if (choice == 3)
	{
		int depth=5;
		cout << "You want to run benchmark with depth...(Recommendation: 4 or 5)" << endl;
		cin >> depth;
		int round=1;
		cout << "You want to repeat benchmark for how many rounds?" << endl;
		cin >> round;
		RunTimeBenchmark(depth, round);
	}
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
/*
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
*/
static void twoPlayerGame()
{
	board theboard;
	theboard.printBoard(false,false);
	while (true)
	{
		if (theboard.player == White)
		{
			std::cout << "White's turn" << endl;
		}
		else
		{
			std::cout << "Black's turn" << endl;
		}
		pair<Loc,Loc> userMove = AskForMove();
		theboard.MoveByHuman(userMove);
		theboard.printBoard(false,false);
	}
	theboard.printBoard(false,false);
	return;
}

Loc decodeLoc(const std::string& notation) {
	if (notation.length() != 2) {
		// Invalid notation length
		throw std::invalid_argument("Chess notation must be exactly 2 characters");
	}

	char file = notation[0];
	char rank = notation[1];

	// Convert file (column) to 0-7
	int fileIndex;
	if (file >= 'A' && file <= 'H') {
		fileIndex = file - 'A';
	}
	else if (file >= 'a' && file <= 'h') {
		fileIndex = file - 'a';
	}
	else {
		throw std::invalid_argument("Invalid file (must be A-H or a-h)");
	}

	// Convert rank (row) to 0-7
	int rankIndex;
	if (rank >= '1' && rank <= '8') {
		rankIndex = rank - '1';
	}
	else {
		throw std::invalid_argument("Invalid rank (must be 1-8)");
	}

	// Calculate the location index based on our enum layout
	int index = rankIndex * 8 + fileIndex;

	return static_cast<Loc>(index);
}

string encodeLoc(Loc loc) {
	uint8_t rank = getRank(loc);
	uint8_t file = getFile(loc);
	string result;
	result += ('A' + file);
	result += ('1' + rank);
	return result;
}

static pair<Loc,Loc> AskForMove()
{
	string piece;
	string target;
	std::cout <<"Enter the location of your piece and target (e.g. D2 D4)" << endl;
	std::cin >> piece;
	std::cin >> target;
	return { decodeLoc(piece),decodeLoc(target) };
}

static void PlayWithComputer()
{
	int depth;
	board theboard;
	bool unicode=PromptForUnicodeSupport();
	theboard.printBoard(false, unicode);
	cout << "Computer Smartness: (Recommended is 4. If you set it to 5, it will take several minutes to compute in complex situations.)" << endl;
	cin >> depth;
	cout << "You want to play: (B/W)" << endl;
	char user;
	cin >> user;
	if (user == 'W' || user == 'w')
	{
		system("cls");
		theboard.printBoard(false, unicode);
		while (true)
		{
			if (theboard.player == Black)
			{
				cout << "Computer is thinking..." << endl;
				using namespace std::chrono;
				duration<double> consume;
				high_resolution_clock::time_point begin;
				high_resolution_clock::time_point finish;
				begin = high_resolution_clock::now();
				pair<Loc,Loc> bestMove = theboard.findBlackBestMove(depth);
				finish = high_resolution_clock::now();
				consume += duration_cast<duration<double>>(finish - begin);
				cout << "After thinking for " << consume.count() << " seconds, the computer plays: " << encodeLoc(bestMove.first) << "-->" << encodeLoc(bestMove.second) << endl;
				theboard.MoveByEngine(bestMove);
				theboard.printBoard(false,unicode);
			}
			else
			{
				pair<Loc, Loc> userMove = AskForMove();
				system("cls");
				cout << "You play: " << encodeLoc(userMove.first) << "-->" << encodeLoc(userMove.second) << endl;
				theboard.MoveByHuman(userMove);
				theboard.printBoard(false, unicode);
			}
		}
	}
	else
	{
		system("cls");
		theboard.printBoard(false, unicode);
		vector<pair<Loc, Loc>> allPossibleMoves = theboard.getAllPossibleMovesForEngine();
		while (!theboard.isBlackCheckmated(allPossibleMoves) && !theboard.isWhiteCheckmated(allPossibleMoves))
		{
			if (theboard.player == White)
			{
				cout << "Computer is thinking..." << endl;
				using namespace std::chrono;
				duration<double> consume;
				high_resolution_clock::time_point begin;
				high_resolution_clock::time_point finish;
				begin = high_resolution_clock::now();
				pair<Loc, Loc> bestMove = theboard.findWhiteBestMove(depth);
				finish = high_resolution_clock::now();
				consume += duration_cast<duration<double>>(finish - begin);
				cout << "After thinking for " << consume.count() << " seconds, the computer plays: " << encodeLoc(bestMove.first) << "-->" << encodeLoc(bestMove.second) << endl;
				theboard.MoveByEngine(bestMove);
				theboard.printBoard(false, unicode);
			}
			else
			{
				pair<Loc, Loc> userMove = AskForMove();
				system("cls");
				cout << "You play: " << encodeLoc(userMove.first) << "-->" << encodeLoc(userMove.second) << endl;
				theboard.MoveByHuman(userMove);
				theboard.printBoard(false, unicode);
			}
			allPossibleMoves = theboard.getAllPossibleMovesForEngine();
		}
	}
	cout << "Game Over" << endl;
}

static void RunTimeBenchmark(int depth, int round)
{
	using namespace std::chrono;
	duration<double> currrent1, currrent2, currrent3, currrent4;
	high_resolution_clock::time_point begin;
	high_resolution_clock::time_point finish;

	system("cls");
	for (int i = 0; i < round; i++)
	{
		cout << "Benchmarking..." << i + 1 << "/" << round << endl;
		board testBoard;
		testBoard.MoveByHuman({D2, D4});
		testBoard.MoveByHuman({D7, D5});
		testBoard.MoveByHuman({B1, C3});
		begin = high_resolution_clock::now();
		testBoard.findBlackBestMove(depth);
		finish = high_resolution_clock::now();
		cout << "test 1 of 4 done." << endl;
		currrent1 += duration_cast<duration<double>>(finish - begin) / round;
		testBoard.MoveByHuman({C8, E6});
		begin = high_resolution_clock::now();
		testBoard.findWhiteBestMove(depth);
		finish = high_resolution_clock::now();
		cout << "test 2 of 4 done. The rest may take longer to run." << endl;
		currrent2 += duration_cast<duration<double>>(finish - begin) / round;

		testBoard.MoveByHuman({E2, E4});
		testBoard.MoveByHuman({D5, E4});
		testBoard.MoveByHuman({C3, E4});
		testBoard.MoveByHuman({D8, D5});
		testBoard.MoveByHuman({F2, F3});
		testBoard.MoveByHuman({B8, C6});
		testBoard.MoveByHuman({C1, E3});
		testBoard.MoveByHuman({E8, C8});
		testBoard.MoveByHuman({G1, E2});
		testBoard.MoveByHuman({G7, G6});
		begin = high_resolution_clock::now();
		testBoard.findWhiteBestMove(depth);
		finish = high_resolution_clock::now();
		cout << "test 3 of 4 done." << endl;
		currrent3 += duration_cast<duration<double>>(finish - begin) / round;
		testBoard.MoveByHuman({C2, C3});
		begin = high_resolution_clock::now();
		testBoard.findBlackBestMove(depth);
		finish = high_resolution_clock::now();
		cout << "test 4 of 4 done." << endl;
		currrent4 += duration_cast<duration<double>>(finish - begin) / round;
		if (i< round-1)
		{
			cout << "Waiting..." << endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
		system("cls");
	}
	system("cls");
	cout << "Benchmark Result:" << endl;
	cout << "Board1(B): " << currrent1.count() << "s" << endl;
	cout << "Board2(W): " << currrent2.count() << "s" << endl;
	cout << "Board3(W): " << currrent3.count() << "s" << endl;
	cout << "Board4(B): " << currrent4.count() << "s" << endl;
}