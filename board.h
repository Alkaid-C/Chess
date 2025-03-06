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
#define White true
#define Black false
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
	bool mover;
	bool unicodeSupported;
	vector<pair<pair<int, int>, pair<int, int>>> MoveHistory;
	board();
	board(const board& theboard);
	void setUnicodeSupported(bool support);
	void PromptForUnicodeSupport();
	char getPieceAt(int row, int col);
	void setPieceAt(int row, int col, char newPiece);
	void removePiece(int row, int col);
	void PieceCast(char piece);
	void printBoard();
	int getWhiteMaterialAdvantage() const;
	int getBlackMaterialAdvantage() const;
	bool isWhite(const int& row, const int& col) const;
	bool isBlack(const int& row, const int& col) const;
	bool isInTheBoard(const int& row, const int& col) const;
	vector<pair<int, int>> WhiteOccupiedSquares() const;
	vector<pair<int, int>> BlackOccupiedSquares() const;
	vector<pair<int, int>> WhiteControlledSquares() const;
	vector<pair<int, int>> BlackControlledSquares() const;
	bool isWhiteControlled(int row, int col) const;
	bool isBlackControlled(int row, int col) const;
	bool isWhiteChecked() const;
	bool isBlackChecked() const;
	bool willWhiteBeChecked(int row, int col, int newRow, int newCol) const;
	bool willBlackBeChecked(int row, int col, int newRow, int newCol) const;
	bool isWhiteCheckmated();
	bool isBlackCheckmated();
	bool isWhiteStalemated();
	bool isBlackStalemated();
	vector<pair<int, int>> getPossibleMoves(int row, int col) const;
	vector<pair<int, int>> getPossibleEnPassant(int row, int col) const;
	vector<pair<int, int>> getPossibleCastling(int row, int col) const;
	vector<pair<pair < int, int>, pair<int, int>> > getAllWhitePossibleMoves() const;
	vector<pair<pair < int, int>, pair<int, int>> > getAllBlackPossibleMoves() const;
	bool move(int row, int col, int newRow, int newCol);
	void moveNoCheck(int row, int col, int newRow, int newCol);
	pair<pair<int, int>, pair<int, int>> AlgebraicNotationDecoder(string notation, char mover);
	pair<pair<pair<int, int>, pair<int, int>>, int> findWhiteBestMove(int depth);
	pair<pair<pair<int, int>, pair<int, int>>, int> findBlackBestMove(int depth); 
	int findWhiteBestScore(int depth);
	int findBlackBestScore(int depth);
	void findBlackBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth);
	void findWhiteBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth);
};
#endif // !BOARD_H
