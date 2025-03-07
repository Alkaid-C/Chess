#include<stdint.h>
#define White true
#define Black false
#pragma once

#include <vector>
#include <string>

#ifndef _BOARD_H
#define _BOARD_H
using namespace std;

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7
#define H 8

enum Piece : uint8_t 
{
	Empty = 0x00,

	COLOR_MASK = 0xF0,
	TYPE_MASK = 0x0F,

	WHITE = 0x10,
	BLACK = 0x20,

	Pawn = 0x01,
	Knight = 0x02,
	Biship = 0x03,
	Rook = 0x04,
	Queen = 0x05,
	King = 0x06,

	WhitePawn = 0x11,
	WhiteKnight = 0x12,
	WhiteBishop = 0x13,
	WhiteRook = 0x14,
	WhiteQueen = 0x15,
	WhiteKing = 0x16,

	BlackPawn = 0x21,
	BlackKnight = 0x22,
	BlackBishop = 0x23,
	BlackRook = 0x24,
	BlackQueen = 0x25,
	BlackKing = 0x26,
};

inline bool isWhite(const Piece piece) { return (piece & COLOR_MASK) == Piece::WHITE; }
inline bool isBlack(const Piece piece) { return (piece & COLOR_MASK) == Piece::BLACK; }
inline bool isEmpty(const Piece piece) { return piece == Piece::Empty; }

enum Loc : uint8_t 
{
	A1 = 0, A2 = 1, A3 = 2, A4 = 3, A5 = 4, A6 = 5, A7 = 6, A8 = 7,
	B1 = 8, B2 = 9, B3 = 10, B4 = 11, B5 = 12, B6 = 13, B7 = 14, B8 = 15,
	C1 = 16, C2 = 17, C3 = 18, C4 = 19, C5 = 20, C6 = 21, C7 = 22, C8 = 23,
	D1 = 24, D2 = 25, D3 = 26, D4 = 27, D5 = 28, D6 = 29, D7 = 30, D8 = 31,
	E1 = 32, E2 = 33, E3 = 34, E4 = 35, E5 = 36, E6 = 37, E7 = 38, E8 = 39,
	F1 = 40, F2 = 41, F3 = 42, F4 = 43, F5 = 44, F6 = 45, F7 = 46, F8 = 47,
	G1 = 48, G2 = 49, G3 = 50, G4 = 51, G5 = 52, G6 = 53, G7 = 54, G8 = 55,
	H1 = 56, H2 = 57, H3 = 58, H4 = 59, H5 = 60, H6 = 61, H7 = 62, H8 = 63
};
inline bool isInTheBoard(const Loc loc) { return loc < 64; }
inline Loc operator+(const Loc loc, const uint8_t offset) { return static_cast<Loc>(static_cast<uint8_t>(loc) + static_cast<uint8_t>(offset)); }
inline Loc& operator+=(Loc& loc, const uint8_t offset) { return loc = static_cast<Loc>(static_cast<uint8_t>(loc) + static_cast<uint8_t>(offset)); }


class board 
{
public:
	Piece CurBoard[64];
	vector<Piece> TakenPieceBlack;
	vector<Piece> TakenPieceWhite;
	bool WhiteCastleKingSideQualified;
	bool WhiteCastleQueenSideQualified;
	bool BlackCastleKingSideQualified;
	bool BlackCastleQueenSideQualified;
	bool mover;
	pair<pair<Loc,Loc>,Piece> LastMove;

	board();
	board(const board& theboard);
	inline bool isLocWhite(Loc loc) const;
	inline bool isLocBlack(Loc loc) const;
	inline bool isLocEmpty(Loc loc) const;
	void printPiece(const Piece piece, const bool UnicodeSupport) const;
	void printBoard(const bool Heading, const bool UnicodeSupport) const;
	int_fast8_t getWhiteMaterialAdvantage() const;
	int_fast8_t getBlackMaterialAdvantage() const;
	inline vector<Loc> WhiteOccupiedSquares() const;
	inline vector<Loc> BlackOccupiedSquares() const;
	vector<Loc> WhiteControlledSquares() const;
	vector<Loc> BlackControlledSquares() const;
	bool isWhiteControlled(Loc loc) const;
	bool isBlackControlled(Loc loc) const;
	bool isWhiteChecked() const;
	bool isBlackChecked() const;
	bool willWhiteBeChecked(pair<Loc,Loc>) const;
	bool willBlackBeChecked(pair<Loc,Loc>) const;
	bool isWhiteCheckmated() const;
	bool isBlackCheckmated() const;
	bool isWhiteStalemated() const;
	bool isBlackStalemated() const;
	vector<Loc> getPossibleMoves(int row, int col) const;
	vector<Loc> getPossibleEnPassant(int row, int col) const;
	vector<Loc> getPossibleCastling(int row, int col) const;
	vector<pair<Loc,Loc>> getAllWhitePossibleMoves() const;
	vector<pair<Loc,Loc>> getAllBlackPossibleMoves() const;
	bool move(pair<Loc,Loc>);
	void moveNoCheck(pair<Loc,Loc>);
	pair<pair<pair<int, int>, pair<int, int>>, int> findWhiteBestMove(int depth);
	pair<pair<pair<int, int>, pair<int, int>>, int> findBlackBestMove(int depth); 
	int findWhiteBestScore(int depth);
	int findBlackBestScore(int depth);
	void findBlackBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth);
	void findWhiteBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth);
};
#endif // !BOARD_H
