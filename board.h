#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7
#define H 8
#define BlackRook 'R'
#define WhiteRook 'r'
#define BlackBishop 'S'
#define WhiteBishop 's'
#define BlackKnight 'N'
#define WhiteKnight 'n'
#define BlackQueen 'Q'
#define WhiteQueen 'q'
#define BlackPawn 'P'
#define WhitePawn 'p'
#define BlackKing 'K'
#define WhiteKing 'k'
#define Empty '*'
#define White 'w'
#define Black 'b'
#pragma once

#include <vector>
#include <string>

#ifndef _BOARD_H
#define _BOARD_H
using namespace std;




class board 
{
public:
	vector<vector<char>> CurBoard;
	vector<char> TakenPieceBlack;
	vector<char> TakenPieceWhite;
	bool WhiteCastleKingSideQualified;
	bool WhiteCastleQueenSideQualified;
	bool BlackCastleKingSideQualified;
	bool BlackCastleQueenSideQualified;
	vector<pair<pair<int_fast8_t, int_fast8_t>, pair<int_fast8_t, int_fast8_t>>> MoveHistory;
	board();
	board(const board& theboard);
	char getPieceAt(int_fast8_t row, int_fast8_t col);
	void setPieceAt(int_fast8_t row, int_fast8_t col, char newPiece);
	void removePiece(int_fast8_t row, int_fast8_t col);
	void printBoard();
	int getWhiteMaterialAdvantage();
	int getBlackMaterialAdvantage();
	bool isWhite(int_fast8_t row, int_fast8_t col);
	bool isBlack(int_fast8_t row, int_fast8_t col);
	bool isInTheBoard(int_fast8_t row, int_fast8_t col);
	vector<pair<int_fast8_t, int_fast8_t>> WhiteOccupiedSquares();
	vector<pair<int_fast8_t, int_fast8_t>> BlackOccupiedSquares();
	vector<pair<int_fast8_t, int_fast8_t>> WhiteControlledSquares();
	vector<pair<int_fast8_t, int_fast8_t>> BlackControlledSquares();
	bool isWhiteControlled(int_fast8_t row, int_fast8_t col);
	bool isBlackControlled(int_fast8_t row, int_fast8_t col);
	bool isWhiteChecked();
	bool isBlackChecked();
	bool isWhiteCheckmated();
	bool isBlackCheckmated();
	vector<pair<int_fast8_t, int_fast8_t>> getPossibleMoves(int_fast8_t row, int_fast8_t col);
	vector<pair<int_fast8_t, int_fast8_t>> getPossibleEnPassant(int_fast8_t row, int_fast8_t col);
	vector<pair<int_fast8_t, int_fast8_t>> getPossibleCastling(int_fast8_t row, int_fast8_t col);
	void move(int_fast8_t row, int_fast8_t col, int_fast8_t newRow, int_fast8_t newCol);
	pair<pair<int_fast8_t, int_fast8_t>, pair<int_fast8_t, int_fast8_t>> AlgebraicNotationDecoder(string notation, char mover);
	
};
#endif // !BOARD_H
