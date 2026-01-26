#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>
#include <vector> 
#include <iostream>

#ifndef _STATIC_HELPER
#define _STATIC_HELPER

static void removeDuplicatedMove(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& moves) 
{
	std::sort(moves.begin(), moves.end());
	moves.erase(std::unique(moves.begin(), moves.end()), moves.end());
}

static void removeDuplicatedLoc(std::vector<std::pair<int, int>>& locs) {
	std::sort(locs.begin(), locs.end());
	locs.erase(std::unique(locs.begin(), locs.end()), locs.end());
}

bool PromptForUnicodeSupport()
{
	using namespace std;
	system("chcp 65001");
	cout << "Does your terminal support unicode characters? (Y/N)" << endl;
	cout << "For example, is this white pawn (" << u8"\u2659" << ") correctly displayed ? If not, type N." << endl;
	char unicode;
	cin >> unicode;
	if (unicode == 'Y')
	{
		cout << "In this case, the pieces will be displayed as follows:" << endl;
		cout << "White Pawn: " << u8"\u2659" << endl;
		cout << "White Rook: " << u8"\u2656" << endl;
		cout << "White Knight: " << u8"\u2658" << endl;
		cout << "White Bishop: " << u8"\u2657" << endl;
		cout << "White Queen: " << u8"\u2655" << endl;
		cout << "White King: " << u8"\u2654" << endl;
		cout << "Black Pawn: " << u8"\u265F" << endl;
		cout << "Black Rook: " << u8"\u265C" << endl;
		cout << "Black Knight: " << u8"\u265E" << endl;
		cout << "Black Bishop: " << u8"\u265D" << endl;
		cout << "Black Queen: " << u8"\u265B" << endl;
		cout << "Black King: " << u8"\u265A" << endl;
		cout << "Empty Square: *" << endl;
		return true;
	}
	else
	{
		cout << "In this case, the pieces will be displayed as follows:" << endl;
		cout << "White Pawn: p" << endl;
		cout << "White Rook: r" << endl;
		cout << "White Knight: n" << endl;
		cout << "White Bishop: s" << endl;
		cout << "White Queen: q" << endl;
		cout << "White King: k" << endl;
		cout << "Black Pawn: P" << endl;
		cout << "Black Rook: R" << endl;
		cout << "Black Knight: N" << endl;
		cout << "Black Bishop: S" << endl;
		cout << "Black Queen: Q" << endl;
		cout << "Black King: K" << endl;
		cout << "Empty Square: *" << endl;
		return false;
	}
}
#endif