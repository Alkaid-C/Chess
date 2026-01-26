#include<stdint.h>

#pragma once

#include <vector>
#include <string>

#ifndef _BOARD_H
#define _BOARD_H
using namespace std;



enum Player : bool
{
	White = true,
	Black = false
};

enum Piece : uint8_t 
{
	Empty = 0x00,

	COLOR_MASK = 0xF0,
	TYPE_MASK = 0x0F,

	WHITE = 0x10,
	BLACK = 0x20,

	Pawn = 0x01,
	Knight = 0x02,
	Bishop = 0x03,
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
inline bool isPawn(const Piece piece) { return (piece & TYPE_MASK) == Piece::Pawn; }
inline bool isKnight(const Piece piece) { return (piece & TYPE_MASK) == Piece::Knight; }
inline bool isBishop(const Piece piece) { return (piece & TYPE_MASK) == Piece::Bishop; }
inline bool isRook(const Piece piece) { return (piece & TYPE_MASK) == Piece::Rook; }
inline bool isQueen(const Piece piece) { return (piece & TYPE_MASK) == Piece::Queen; }
inline bool isKing(const Piece piece) { return (piece & TYPE_MASK) == Piece::King; }

enum Rank : uint8_t
{
	Rank1 = 0,
	Rank2 = 1,
	Rank3 = 2,
	Rank4 = 3,
	Rank5 = 4,
	Rank6 = 5,
	Rank7 = 6,
	Rank8 = 7
};
enum File : uint8_t
{
	FileA = 0,
	FileB = 1,
	FileC = 2,
	FileD = 3,
	FileE = 4,
	FileF = 5,
	FileG = 6,
	FileH = 7
};
enum Loc : uint8_t 
{
	A1 = 000, B1 = 001, C1 = 002, D1 = 003, E1 = 004, F1 = 005, G1 = 006, H1 = 007,
	A2 = 010, B2 = 011, C2 = 012, D2 = 013, E2 = 014, F2 = 015, G2 = 016, H2 = 017,
	A3 = 020, B3 = 021, C3 = 022, D3 = 023, E3 = 024, F3 = 025, G3 = 026, H3 = 027,
	A4 = 030, B4 = 031, C4 = 032, D4 = 033, E4 = 034, F4 = 035, G4 = 036, H4 = 037,
	A5 = 040, B5 = 041, C5 = 042, D5 = 043, E5 = 044, F5 = 045, G5 = 046, H5 = 047,
	A6 = 050, B6 = 051, C6 = 052, D6 = 053, E6 = 054, F6 = 055, G6 = 056, H6 = 057,
	A7 = 060, B7 = 061, C7 = 062, D7 = 063, E7 = 064, F7 = 065, G7 = 066, H7 = 067,
	A8 = 070, B8 = 071, C8 = 072, D8 = 073, E8 = 074, F8 = 075, G8 = 076, H8 = 077,
	IrregularMoveTag=0xFF
};
const uint8_t RookDirection[4] = { 1,8,248,255 };
const uint8_t BishopDirection[4] = { 7,9,247,249 };
const uint8_t QueenDirection[8] = { 1,7,8,9,247,248,249,255 };
const uint8_t KnightMoves[8] = { 6,10,15,17,239,241,246,250 };
inline bool isInTheBoard(const Loc loc) { return loc < 64; }
inline Loc operator+(const Loc loc, const uint8_t offset) { return static_cast<Loc>(static_cast<uint8_t>(loc) + static_cast<uint8_t>(offset)); }
inline Loc& operator+=(Loc& loc, const uint8_t offset) { return loc = static_cast<Loc>(static_cast<uint8_t>(loc) + static_cast<uint8_t>(offset)); }
inline uint8_t getRank(const Loc loc) { return loc >> 3; }
inline uint8_t getFile(const Loc loc) { return loc & 07; }
inline Loc getLoc(uint8_t rank, uint8_t file) { return (Loc)(rank * 8 + file); }


class board 
{
public:
	Piece CurBoard[64];
	vector<Piece> TakenPieceBlack;
	vector<Piece> TakenPieceWhite;
	bool CastlingQualified[4];//BlackKingSide,BlackQueenSide,WhiteKingSide,WhiteQueenside
	Player player;
	pair<Loc,Loc> LastMove;

	board();
	board(const board& theboard);
	inline bool isLocWhite(Loc loc) const { return isWhite(CurBoard[loc]); }
	inline bool isLocBlack(Loc loc) const { return isBlack(CurBoard[loc]); }
	inline bool isLocPawn(const Loc loc) const { return isPawn(CurBoard[loc]); }
	inline bool isLocKnight(const Loc loc) const { return isKnight(CurBoard[loc]); }
	inline bool isLocBishop(const Loc loc) const { return isBishop(CurBoard[loc]); }
	inline bool isLocRook(const Loc loc) const { return isRook(CurBoard[loc]); }
	inline bool isLocQueen(const Loc loc) const { return isQueen(CurBoard[loc]); }
	inline bool isLocKing(const Loc loc) const { return isKing(CurBoard[loc]); }
	inline bool isLocEmpty(const Loc loc) const { return isEmpty(CurBoard[loc]); }
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
	inline bool willWhiteBeCheckedForHuman(pair<Loc,Loc>) const;
	inline bool willBlackBeCheckedForHuman(pair<Loc,Loc>) const;
	inline bool willWhiteBeCheckedForEngine(pair<Loc, Loc>) const;
	inline bool willBlackBeCheckedForEngine(pair<Loc, Loc>) const;
	bool isWhiteCheckmated(const vector<pair<Loc, Loc>>& AllWhitePossibleMoveNoChcek) const;
	bool isBlackCheckmated(const vector<pair<Loc, Loc>>& AllBlackPossibleMoveNoChcek) const;
	bool isWhiteStalemated(const vector<pair<Loc, Loc>>& AllWhitePossibleMoveNoChcek) const;
	bool isBlackStalemated(const vector<pair<Loc, Loc>>& AllBlackPossibleMoveNoChcek) const;
	vector<pair<Loc, Loc>> getPossibleRegularMovesRaw() const;
	vector<Loc> getPossibleEnPassantRaw() const;
	vector<Loc> getPossibleCastlingRaw() const;
	vector<pair<Loc, Loc>> getAllLegalMovesForHuman() const;
	vector<pair<Loc, Loc>> getAllPossibleMovesForEngine() const;
	void MoveByHuman(const pair<Loc,Loc>);
	void MoveByEngine(const pair<Loc,Loc>);
	pair<Loc, Loc> findWhiteBestMove(int depth) const;
	pair<Loc, Loc> findBlackBestMove(int depth) const;
	void findWhiteBestMoveCore(pair<Loc, Loc>& attemptMove, int_fast8_t& bestScoreT, uint8_t depth) const;
	void findBlackBestMoveCore(pair<Loc, Loc>& attemptMove, int_fast8_t& bestScoreT, uint8_t depth) const;
	int_fast8_t findWhiteBestScore(uint8_t depth) const;
	int_fast8_t findBlackBestScore(uint8_t depth) const;
};
#endif // !BOARD_H
