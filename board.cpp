
#include "board.h"
#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstring>
#include <assert.h>
#include <set>

#pragma execution_character_set("utf-8")

    board::board()
    {
		for (int i = 16; i < 48; i++) {
			CurBoard[i] = Piece::Empty;
		}

		CurBoard[Loc::A2] = Piece::WhitePawn;
		CurBoard[Loc::B2] = Piece::WhitePawn;
		CurBoard[Loc::C2] = Piece::WhitePawn;
		CurBoard[Loc::D2] = Piece::WhitePawn;
		CurBoard[Loc::E2] = Piece::WhitePawn;
		CurBoard[Loc::F2] = Piece::WhitePawn;
		CurBoard[Loc::G2] = Piece::WhitePawn;
		CurBoard[Loc::H2] = Piece::WhitePawn;

		CurBoard[Loc::A7] = Piece::BlackPawn;
		CurBoard[Loc::B7] = Piece::BlackPawn;
		CurBoard[Loc::C7] = Piece::BlackPawn;
		CurBoard[Loc::D7] = Piece::BlackPawn;
		CurBoard[Loc::E7] = Piece::BlackPawn;
		CurBoard[Loc::F7] = Piece::BlackPawn;
		CurBoard[Loc::G7] = Piece::BlackPawn;
		CurBoard[Loc::H7] = Piece::BlackPawn;

		CurBoard[Loc::A1] = Piece::WhiteRook;
		CurBoard[Loc::B1] = Piece::WhiteKnight;
		CurBoard[Loc::C1] = Piece::WhiteBishop;
		CurBoard[Loc::D1] = Piece::WhiteQueen;
		CurBoard[Loc::E1] = Piece::WhiteKing;
		CurBoard[Loc::F1] = Piece::WhiteBishop;
		CurBoard[Loc::G1] = Piece::WhiteKnight;
		CurBoard[Loc::H1] = Piece::WhiteRook;

		CurBoard[Loc::A8] = Piece::BlackRook;
		CurBoard[Loc::B8] = Piece::BlackKnight;
		CurBoard[Loc::C8] = Piece::BlackBishop;
		CurBoard[Loc::D8] = Piece::BlackQueen;
		CurBoard[Loc::E8] = Piece::BlackKing;
		CurBoard[Loc::F8] = Piece::BlackBishop;
		CurBoard[Loc::G8] = Piece::BlackKnight;
		CurBoard[Loc::H8] = Piece::BlackRook;

        TakenPieceBlack = {};
        TakenPieceWhite = {};
		CastlingQualified[0] = true;
		CastlingQualified[1] = true;
		CastlingQualified[2] = true;
		CastlingQualified[3] = true;
		LastMove = {};
		player = White;
    }
	board::board(const board& theboard)
	{
		memcpy(CurBoard, theboard.CurBoard, sizeof(CurBoard));
		TakenPieceBlack = theboard.TakenPieceBlack;
		TakenPieceWhite = theboard.TakenPieceWhite;
		CastlingQualified[0] = theboard.CastlingQualified[0];
		CastlingQualified[1] = theboard.CastlingQualified[1];
		CastlingQualified[2] = theboard.CastlingQualified[2];
		CastlingQualified[3] = theboard.CastlingQualified[3];
		LastMove = theboard.LastMove;
		player = theboard.player;
	}
	void board::printPiece(const Piece piece, const bool UnicodeSupported) const
	{
		if (!UnicodeSupported)
		{
			switch (piece)
			{
			case Piece::WhitePawn:
				cout << 'p';
				break;
			case Piece::WhiteRook:
				cout << 'r';
				break;
			case Piece::WhiteKnight:
				cout << 'n';
				break;
			case Piece::WhiteBishop:
				cout << 'b';
				break;
			case Piece::WhiteQueen:
				cout << 'q';
				break;
			case Piece::WhiteKing:
				cout << 'k';
				break;
			case Piece::BlackPawn:
				cout << 'P';
				break;
			case Piece::BlackRook:
				cout << 'R';
				break;
			case Piece::BlackKnight:
				cout << 'N';
				break;
			case Piece::BlackBishop:
				cout << 'B';
				break;
			case Piece::BlackQueen:
				cout << 'Q';
				break;
			case Piece::BlackKing:
				cout << 'K';
				break;
			case Piece::Empty:
				cout << '*';
			}
		}
		else
		{
			switch (piece)
			{
			case Piece::WhitePawn:
				cout << u8"\u2659";
				break;
			case Piece::WhiteRook:
				cout << u8"\u2656";
				break;
			case Piece::WhiteKnight:
				cout << u8"\u2658";
				break;
			case Piece::WhiteBishop:
				cout << u8"\u2657";
				break;
			case Piece::WhiteQueen:
				cout << u8"\u2655";
				break;
			case Piece::WhiteKing:
				cout << u8"\u2654";
				break;
			case Piece::BlackPawn:
				cout << u8"\u265F";
				break;
			case Piece::BlackRook:
				cout << u8"\u265C";
				break;
			case Piece::BlackKnight:
				cout << u8"\u265E";
				break;
			case Piece::BlackBishop:
				cout << u8"\u265D";
				break;
			case Piece::BlackQueen:
				cout << u8"\u265B";
				break;
			case Piece::BlackKing:
				cout << u8"\u265A";
				break;
			case Piece::Empty:
				cout << '*';
			}
		}
		return;
	}
	void board::printBoard(const bool Heading, const bool UnicodeSupported) const
	{
		cout << "-----------------" << endl;
		if (Heading == White)
		{
			cout << "  A B C D E F G H" << endl;
			for (int_fast8_t i = 7; i >= 0; i--)
			{
				cout << i + 1;
				for (int_fast8_t j = 0; j < 8; j++)
				{
					cout << " ";
					printPiece(CurBoard[i * 8 + j], UnicodeSupported);
				}
				cout << " " << i + 1 << endl;
			}
			cout << "  A B C D E F G H" << endl;
		}
		else
		{
			cout << "  H G F E D C B A" << endl;
			for (int_fast8_t i = 0; i < 8; i++)
			{
				cout << i + 1;
				for (int_fast8_t j = 7; j >= 0; j--)
				{
					cout << " ";
					printPiece(CurBoard[i*8+j], UnicodeSupported);
				}
				cout << " " << i + 1 << endl;
			}
			cout << "  H G F E D C B A" << endl;
		}
		bool gameend = false;

		vector<pair<Loc, Loc>> AllPossibleMoves = getAllPossibleMovesForEngine();
		if (player==White)
		{
			if (isBlackCheckmated(AllPossibleMoves) == true)
			{ 
				cout << "White Wins" << endl;
				gameend = true;
			}
		}
		else 
		{
			if (isWhiteCheckmated(AllPossibleMoves) == true)
			{
				cout << "Black Wins" << endl;
				gameend = true;
			}
		}
		if (gameend == false)
		{
			if (getWhiteMaterialAdvantage() >= 0)
			{
				cout << "White Material Advantage:" << getWhiteMaterialAdvantage() << endl;
			}
			else
			{
				cout << "Black Material Advantage:" << getBlackMaterialAdvantage() << endl;
			}
		}
		cout << "-----------------" << endl;

	}
	int_fast8_t board::getWhiteMaterialAdvantage() const
	{
		int_fast8_t WhiteAdv = 0;
		int WhiteValueOnBoard = 0;
		for (uint_fast8_t i =0; i<64; i++ )
		{

			switch (CurBoard[i])
			{
			case Piece::WhitePawn:
				WhiteAdv += 1;
				break;
			case Piece::WhiteRook:
				WhiteAdv += 5;
				break;
			case Piece::WhiteKnight:
				WhiteAdv += 3;
				break;
			case Piece::WhiteBishop:
				WhiteAdv += 3;
				break;
			case Piece::WhiteQueen:
				WhiteAdv += 9;
				break;
			case Piece::BlackPawn:
				WhiteAdv -= 1;
				break;
			case Piece::BlackRook:
				WhiteAdv -= 5;
				break;
			case Piece::BlackKnight:
				WhiteAdv -= 3;
				break;
			case Piece::BlackBishop:
				WhiteAdv -= 3;
				break;
			case Piece::BlackQueen:
				WhiteAdv -= 9;
				break;
			}
		}
		return WhiteAdv;
	}
	int_fast8_t board::getBlackMaterialAdvantage() const
	{
		return 0 - getWhiteMaterialAdvantage();
	}
	vector<Loc> board::WhiteOccupiedSquares() const
	{
		vector<Loc> result;
		result.reserve(16);
		for (uint8_t i = 0; i < 64; i++)
		{
			if (isWhite(CurBoard[i]))
				result.push_back((Loc)i);
		}
		return result;
	}
	vector<Loc> board::BlackOccupiedSquares() const
	{
		vector<Loc> result;
		result.reserve(16);
		for (uint8_t i = 0; i < 64; i++)
		{
			if (isBlack(CurBoard[i]))
				result.push_back((Loc)i);
		}
		return result;
	}
	vector<Loc> board::WhiteControlledSquares() const
	{
		vector<Loc> const WhitePiecesLoc = WhiteOccupiedSquares();
		vector<Loc> result;
		result.reserve(64);
		bool Open;
		Loc attemptLoc;

		for (const Loc& PieceLoc:WhitePiecesLoc)
		{
			switch (CurBoard[PieceLoc])
			{
			case Piece::WhitePawn:
				attemptLoc = PieceLoc + (uint8_t)9;
				if (isInTheBoard(attemptLoc))
				{
					result.push_back(attemptLoc);
				}
				attemptLoc = PieceLoc + (uint8_t)7;
				if (isInTheBoard(attemptLoc))
				{
					result.push_back(attemptLoc);
				}
				break;
			case Piece::WhiteKnight:
				for (uint8_t move : KnightMoves)
				{
					attemptLoc = PieceLoc + move;
					if (isInTheBoard(attemptLoc))
					{
						result.push_back(attemptLoc);
					}
				}
				break;
			case Piece::WhiteBishop:
				for (uint8_t direction : BishopDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::WhiteRook:
				for (uint8_t direction : RookDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::WhiteQueen:
				for (uint8_t direction : QueenDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::WhiteKing:
				for (uint8_t move : QueenDirection)
				{
					attemptLoc = PieceLoc + move;
					if (isInTheBoard(attemptLoc))
					{
						result.push_back(attemptLoc);
					}
				}
				break;
			}
		}
		return result;
	}
	vector<Loc> board::BlackControlledSquares() const
	{
		vector<Loc> const BlackPieceLoc = BlackOccupiedSquares();
		vector<Loc> result;

		result.reserve(64);

		bool Open;
		Loc attemptLoc;

		for (const Loc& PieceLoc : BlackPieceLoc)
		{
			switch (CurBoard[PieceLoc])
			{
			case Piece::BlackPawn:
				attemptLoc = PieceLoc + (uint8_t)247;
				if (isInTheBoard(attemptLoc))
				{
					result.push_back(attemptLoc);
				}
				attemptLoc = PieceLoc + (uint8_t)249;
				if (isInTheBoard(attemptLoc))
				{
					result.push_back(attemptLoc);
				}
				break;
			case Piece::BlackRook:
				for (uint8_t direction : RookDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::BlackKnight:
				for (uint8_t move : KnightMoves)
				{
					attemptLoc = PieceLoc + move;
					if (isInTheBoard(attemptLoc))
					{
						result.push_back(attemptLoc);
					}
				}
				break;
			case Piece::BlackBishop:
				for (uint8_t direction : BishopDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::BlackQueen:
				for (uint8_t direction : QueenDirection)
				{
					Open = true;
					attemptLoc = PieceLoc + direction;
					while (Open)
					{
						if (isInTheBoard(attemptLoc))
						{
							if (isLocEmpty(attemptLoc))
							{
								result.push_back(attemptLoc);
								attemptLoc += direction;
							}
							else
							{
								result.push_back(attemptLoc);
								Open = false;
							}
						}
						else
						{
							Open = false;
						}
					}
				}
				break;
			case Piece::BlackKing:
				for (uint8_t move : QueenDirection)
				{
					attemptLoc = PieceLoc + move;
					if (isInTheBoard(attemptLoc))
					{
						result.push_back(attemptLoc);
					}
				}
				break;
			}
		}
		return result;
	}
	bool board::isWhiteControlled(Loc loc) const
	{
		const vector<Loc> WhiteControlled = WhiteControlledSquares();
		return std::find(WhiteControlled.begin(), WhiteControlled.end(), loc) != WhiteControlled.end();
	}
	bool board::isBlackControlled(Loc loc) const
	{
		const vector<Loc> BlackControlled = BlackControlledSquares();
		return std::find(BlackControlled.begin(), BlackControlled.end(), loc) != BlackControlled.end();
	}
	inline bool board::isWhiteChecked() const
	{
		const vector<Loc> BlackControlled = BlackControlledSquares();
		for (const Loc& loc : BlackControlled)
		{
			if ( CurBoard[loc] == WhiteKing)
			{
				return true;
			}
		}
		return false;
	}
	inline bool board::isBlackChecked() const
	{
		const vector<Loc> WhiteControlled = WhiteControlledSquares();
		for (const Loc& loc : WhiteControlled)
		{
			if (CurBoard[loc] == BlackKing)
			{
				return true;
			}
		}
		return false;
	}
	bool board::willWhiteBeCheckedForHuman(pair<Loc,Loc> move) const
	{ 
		board NewBoard = *this;
		NewBoard.MoveByHuman(move);
		return NewBoard.isWhiteChecked();
	}
	bool board::willBlackBeCheckedForHuman(pair<Loc, Loc> move) const
	{
		board NewBoard = *this;
		NewBoard.MoveByHuman(move);
		return NewBoard.isBlackChecked();
	}
	bool board::willWhiteBeCheckedForEngine(pair<Loc, Loc> move) const
	{
		board NewBoard = *this;
		NewBoard.MoveByEngine(move);
		return NewBoard.isWhiteChecked();
	}
	bool board::willBlackBeCheckedForEngine(pair<Loc, Loc> move) const
	{
		board NewBoard = *this;
		NewBoard.MoveByEngine(move);
		return NewBoard.isBlackChecked();
	}
	bool board::isWhiteCheckmated(const vector<pair<Loc, Loc>>& AllWhitePossibleMoveNoChcek) const
	{
		if (!isWhiteChecked())
		{
			return false; 
		}
		else
		{
		
			for (const pair<Loc, Loc>& move : AllWhitePossibleMoveNoChcek)
			{

				if (!willWhiteBeCheckedForEngine(move))
				{
					return false;
				}
			}
			return true;
		}
	}
	bool board::isBlackCheckmated(const vector<pair<Loc, Loc>>& AllBlackPossibleMoveNoChcek) const
	{
		if (!isBlackChecked())
		{
			return false; 
		}
		else
		{
			for (const pair<Loc, Loc>& move : AllBlackPossibleMoveNoChcek)
			{

				if (!willBlackBeCheckedForEngine(move))
				{
					return false;
				}
			}
			return true;
		}
	}
	bool board::isWhiteStalemated(const vector<pair<Loc, Loc>>& AllWhitePossibleMoveNoChcek) const
	{
		if (isWhiteChecked())
		{
			return false;
		}
		else
		{
			for (const pair<Loc, Loc>& move : AllWhitePossibleMoveNoChcek)
			{

				if (!willWhiteBeCheckedForEngine(move))
				{
					return false;
				}
			}
			return true;
		}
	}
	bool board::isBlackStalemated(const vector<pair<Loc, Loc>>& AllBlackPossibleMoveNoChcek) const
	{
		if (isBlackChecked())
		{
			return false;
		}
		else
		{
			for (const pair<Loc, Loc>& move : AllBlackPossibleMoveNoChcek)
			{

				if (!willWhiteBeCheckedForEngine(move))
				{
					return false;
				}
			}
			return true;
		}
	}
	vector<pair<Loc,Loc>> board::getPossibleRegularMovesRaw() const
	{
		vector<pair<Loc, Loc>> result;
		result.reserve(64);
		Loc attemptLoc;
		bool Open;
		if (player == White)
		{
			const vector<Loc> WhitePiecesLoc = WhiteOccupiedSquares();
			for (const Loc& loc : WhitePiecesLoc)
			{
				switch (CurBoard[loc])
				{
				case WhitePawn:
					if (loc > 7 && loc < 16)
					{
						if (isLocEmpty(loc + (uint8_t)16) && isLocEmpty(loc + (uint8_t)8))
						{
							result.push_back({ loc,loc + (uint8_t)16 });
							result.push_back({ loc, loc + (uint8_t)8 });
						}
					}
					else
					{
						attemptLoc = loc + (uint8_t)8;
						if (isLocEmpty(attemptLoc))
						{
							result.push_back({ loc,attemptLoc });
						}
					}
					attemptLoc = loc + (uint8_t)7;
					if (isLocBlack(attemptLoc))
					{
						result.push_back({ loc,attemptLoc });
					}
					attemptLoc += (uint8_t)2;
					if (isLocBlack(attemptLoc))
					{
						result.push_back({ loc,attemptLoc });
					}
					break;
				case WhiteKnight:
					for (uint8_t move : KnightMoves)
					{
						attemptLoc = loc + move;
						if (isInTheBoard(attemptLoc))
						{
							if (!isLocWhite(attemptLoc))
								result.push_back({ loc, attemptLoc });
						}
					}
					break;
				case WhiteBishop:
					for (uint8_t direction : BishopDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocWhite(attemptLoc))
								{
									if (isLocBlack(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
									
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}		
					}
					break;
				case WhiteRook:
					for (uint8_t direction : RookDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocWhite(attemptLoc))
								{
									if (isLocBlack(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}
					}
					break;
				case WhiteQueen:
					for (uint8_t direction : QueenDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocWhite(attemptLoc))
								{
									if (isLocBlack(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}
					}
					break;
				case WhiteKing:
					for (uint8_t move : QueenDirection)
					{
						attemptLoc = loc + move;
						if (isInTheBoard(attemptLoc))
						{
							if (!isLocWhite(attemptLoc))
								result.push_back({ loc, attemptLoc });
						}
					}
					break;
				}
			}
		}
		else
		{
			const vector<Loc> BlackPiecesLoc = BlackOccupiedSquares();
			for (const Loc& loc : BlackPiecesLoc)
			{
				switch (CurBoard[loc])
				{
				case BlackPawn:
					if (loc > 47 && loc < 56)
					{
						if (isLocEmpty(loc + (uint8_t)240) && isLocEmpty(loc + (uint8_t)248))
						{
							result.push_back({ loc,loc + (uint8_t)240 });
							result.push_back({ loc, loc + (uint8_t)248 });
						}
					}
					else
					{
						attemptLoc = loc + (uint8_t)248;
						if (isLocEmpty(attemptLoc))
						{
							result.push_back({ loc,attemptLoc });
						}
					}
					attemptLoc = loc + (uint8_t)247;
					if (isLocWhite(attemptLoc))
					{
						result.push_back({ loc,attemptLoc });
					}
					attemptLoc += (uint8_t)2;
					if (isLocWhite(attemptLoc))
					{
						result.push_back({ loc,attemptLoc });
					}
					break;
				case BlackKnight:
					for (uint8_t move : KnightMoves)
					{
						attemptLoc = loc + move;
						if (isInTheBoard(attemptLoc))
						{
							if (!isLocBlack(attemptLoc))
								result.push_back({ loc, attemptLoc });
						}
					}
					break;
				case BlackBishop:
					for (uint8_t direction : BishopDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocBlack(attemptLoc))
								{
									if (isLocWhite(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}
					}
					break;
				case BlackRook:
					for (uint8_t direction : RookDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocBlack(attemptLoc))
								{
									if (isLocWhite(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}
					}
					break;
				case BlackQueen:
					for (uint8_t direction : QueenDirection)
					{
						Open = true;
						attemptLoc = loc + direction;
						while (Open)
						{
							if (isInTheBoard(attemptLoc))
							{
								if (!isLocBlack(attemptLoc))
								{
									if (isLocWhite(attemptLoc))
									{
										Open = false;
									}
									result.push_back({ loc,attemptLoc });
									attemptLoc += direction;
								}
								else
								{
									Open = false;
								}
							}
							else
							{
								Open = false;
							}
						}
					}
					break;
				case BlackKing:
					for (uint8_t move : QueenDirection)
					{
						attemptLoc = loc + move;
						if (isInTheBoard(attemptLoc))
						{
							if (!isLocBlack(attemptLoc))
								result.push_back({ loc, attemptLoc });
						}
					}
					break;
				}
			}
		}
		assert(result.size() < 64);
		return result;
	}
	vector<Loc> board::getPossibleEnPassantRaw() const
	{
		vector<Loc> result;
		if (LastMove.second > 23 + 8 * player && LastMove.second < 32 + 8 * player && LastMove.first>7 + 40 * player && LastMove.first < 16 + 40 * player && (CurBoard[LastMove.second] & TYPE_MASK)==Piece::Pawn)
		{
			if (isLocPawn(LastMove.second + (uint8_t)1) && isLocWhite(LastMove.second + (uint8_t)1) == player)
			{
				result.push_back(LastMove.second + (uint8_t)1);
			}
			if (isLocPawn(LastMove.second + (uint8_t)255) && isLocWhite(LastMove.second + (uint8_t)255) == player)
			{
				result.push_back(LastMove.second + (uint8_t)255);
			}
		}
		return result;
	}
	vector<Loc> board::getPossibleCastlingRaw() const
	{
		vector<Loc> EnemyControlledSquares;
		vector<Loc> result;
		if (player == White)
		{
			if (CastlingQualified[2] == true && isLocEmpty(F1) && isLocEmpty(G1))//KingSide
			{
				EnemyControlledSquares = WhiteControlledSquares();
				bool threatened = false;
				for (const Loc loc : EnemyControlledSquares)
				{
					if (loc == E1 || loc == F1 || loc == G1)
					{
						threatened = true;
					}
				}
				if (threatened != true)
				{
					result.push_back(G1);
				}
			}
			if (CastlingQualified[3] == true && isLocEmpty(D8) && isLocEmpty(C8) && isLocEmpty(B8))
			{
				if (EnemyControlledSquares.empty())
				{
					EnemyControlledSquares = WhiteControlledSquares();
				}
				bool threatened = false;
				for (const Loc loc : EnemyControlledSquares)
				{
					if (loc == E1 || loc == D1 || loc == C1)
					{
						threatened = true;
					}
				}
				if (threatened != true)
				{
					result.push_back(C1);
				}
			}
		}
		else
		{
			
			if (CastlingQualified[2] == true && isLocEmpty(F8) && isLocEmpty(G8))//KingSide
			{
				EnemyControlledSquares = BlackControlledSquares();
				bool threatened = false;
				for (const Loc loc : EnemyControlledSquares)
				{
					if (loc == E8 || loc == F8 || loc == G8)
					{
						threatened = true;
					}
				}
				if (threatened != true)
				{
					result.push_back(G8);
				}
			}
			if (CastlingQualified[3] == true && isLocEmpty(D8) && isLocEmpty(C8) && isLocEmpty(B8))
			{
				if (EnemyControlledSquares.empty())
				{
					EnemyControlledSquares = BlackControlledSquares();
				}
				bool threatened = false;
				for (const Loc loc : EnemyControlledSquares)
				{
					if (loc == E8 || loc == D8 || loc == C8)
					{
						threatened = true;
					}
				}
				if (threatened != true)
				{
					result.push_back(C8);
				}
			}
		}
		return result;
	}
    vector<pair<Loc, Loc>> board::getAllLegalMovesForHuman() const //this is prepared for human input; computer won't use this function
    {
        vector<pair<Loc, Loc>> AllPossibleMoves = getPossibleRegularMovesRaw();
        vector<Loc> UnprocessedEnPassant = getPossibleEnPassantRaw();
        vector<Loc> UnprocessedCastling = getPossibleCastlingRaw();
        for (Loc pieceLoc : UnprocessedEnPassant)
        {
            Loc target = (Loc)((uint8_t)LastMove.first + (uint8_t)LastMove.second / (uint8_t)2);
            AllPossibleMoves.push_back({ pieceLoc, target });
        }
        for (Loc target : UnprocessedCastling)
        {
            Loc pieceLoc;
            if (target < 8)
            {
                pieceLoc = D1;
            }
            else
            {
                pieceLoc = D8;
            }
            AllPossibleMoves.push_back({ pieceLoc,target });
        }
        assert(AllPossibleMoves.size() < 64);
		if (player == White)
		{
			AllPossibleMoves.erase(remove_if(AllPossibleMoves.begin(), AllPossibleMoves.end(), [this](const pair<Loc, Loc>& attemptMove) { return willWhiteBeCheckedForHuman(attemptMove); }), AllPossibleMoves.end());
		}
		else
		{
			AllPossibleMoves.erase(remove_if(AllPossibleMoves.begin(), AllPossibleMoves.end(), [this](const pair<Loc, Loc>& attemptMove) { return willBlackBeCheckedForHuman(attemptMove); }), AllPossibleMoves.end());
		}
		return AllPossibleMoves;
    }

	vector<pair<Loc, Loc>> board::getAllPossibleMovesForEngine() const
	{
		vector<pair<Loc, Loc>> AllPossibleMoves = getPossibleRegularMovesRaw();
		vector<Loc> UnprocessedEnPassant = getPossibleEnPassantRaw();
		vector<Loc> UnprocessedCastling = getPossibleCastlingRaw();
		for (Loc pieceLoc : UnprocessedEnPassant)
		{
			AllPossibleMoves.push_back({ pieceLoc, IrregularMoveTag });
		}
		for (Loc target : UnprocessedCastling)
		{
			AllPossibleMoves.push_back({ IrregularMoveTag,target });
		}
		return AllPossibleMoves;
	}
	void board::MoveByHuman(const pair<Loc, Loc> move)
	{
		vector<pair<Loc, Loc>> RegularMoves= getPossibleRegularMovesRaw();
		if (find(RegularMoves.begin(), RegularMoves.end(), move) != RegularMoves.end())
		{
			CurBoard[move.second] = CurBoard[move.first];
			CurBoard[move.first] = Piece::Empty;
		}
		else
		{
			if (getRank(move.first)==Rank::Rank1 || getRank(move.first) == Rank::Rank7)//castling
			{
				CurBoard[move.second] = CurBoard[move.first];
				CurBoard[move.first] = Piece::Empty;
				if (getFile(move.second) == FileC)//QueenSide
				{
					CurBoard[getLoc(getRank(move.first), FileD)] = CurBoard[getLoc(getRank(move.first), FileA)];
					CurBoard[getLoc(getRank(move.first), FileA)] = Empty;
				}
				else
				{
					if(getFile(move.second) == FileG)//KingSide
					{
						CurBoard[getLoc(getRank(move.first), FileF)] = CurBoard[getLoc(getRank(move.first), FileH)];
						CurBoard[getLoc(getRank(move.first), FileH)] = Empty;
					}
					else
					{
						throw invalid_argument("Invalid Human Move");
					}
				}
			}
			else//EnPassant
			{
				if (getRank(move.first) == 4 || getRank(move.first) == 5)
				{
					CurBoard[move.second] = CurBoard[move.first];
					CurBoard[move.first] = Piece::Empty;
					CurBoard[getLoc(getRank(move.first), getFile(move.second))] = Piece::Empty;
				}
				else
				{
					throw invalid_argument("Invalid Human Move");
				}

			}
		}
		player = (Player)!player;
	}
	void board::MoveByEngine(const pair<Loc, Loc>move)
	{
		if (move.first != IrregularMoveTag && move.second != IrregularMoveTag)
		{
			CurBoard[move.second] = CurBoard[move.first];
			CurBoard[move.first] = Piece::Empty;
		}
		else if (move.first == IrregularMoveTag)//Castling. For Castling, defining target square is enough to determine the move
		{
			CurBoard[move.second] = CurBoard[getLoc(getRank(move.second),File::FileE)];
			CurBoard[move.first] = Piece::Empty;
			if (getFile(move.second) == FileC)//QueenSide
			{
				CurBoard[getLoc(getRank(move.second), FileD)] = CurBoard[getLoc(getRank(move.second), FileA)];
				CurBoard[getLoc(getRank(move.second), FileA)] = Empty;
			}
			else
			{
				if((getFile(move.second) == FileG))//KingSide
				{
					CurBoard[getLoc(getRank(move.second), FileF)] = CurBoard[getLoc(getRank(move.second), FileH)];
					CurBoard[getLoc(getRank(move.second), FileH)] = Empty;
				}
				else
				{
					throw invalid_argument("Invalid Engine Move");
				}
			}
		}
		else //EnPassant. For EnPassant, defining target square is enough to determine the move
		{
			if(move.second == IrregularMoveTag)
			{
				CurBoard[getLoc((getRank(LastMove.first) + getRank(LastMove.second)) / 2, getFile(LastMove.first))]= CurBoard[move.first];
				CurBoard[move.first] = Piece::Empty;
				CurBoard[LastMove.second] = Piece::Empty;
			}
			else
			{
				throw invalid_argument("Invalid Engine Move");
			}
		}
		player = (Player)!player;
	}
	pair<Loc,Loc> board::findWhiteBestMove(int depth) const
	{
		pair<Loc,Loc> bestMove;
		int_fast8_t bestscore = -128;
		vector<pair<Loc, Loc>> allPossibleMoves = getAllPossibleMovesForEngine();
		const int numThreads = allPossibleMoves.size();
		vector<int_fast8_t> bestScoreT = vector<int8_t>(numThreads);
		std::vector<std::thread> threads;
		for (int i = 0; i < numThreads; i++) 
		{
			bestScoreT[i] == -128;
			threads.push_back
			(
				std::thread(&board::findWhiteBestMoveCore, this, std::ref(allPossibleMoves[i]), std::ref(bestScoreT[i]), depth)
			);
		}
		for (auto& t : threads) {
			t.join();
		}
		bestscore = bestScoreT[0]; 
		vector<pair<Loc,Loc>> BestMoveList;
		BestMoveList.push_back(allPossibleMoves[0]);
		for (int i = 1; i < numThreads; i++)
		{
			if (bestScoreT[i] > bestscore) 
			{
				bestscore = bestScoreT[i];
				BestMoveList.clear();
				BestMoveList.push_back(allPossibleMoves[i]);
			}
			else if (bestScoreT[i] == bestscore) 
			{
				BestMoveList.push_back(allPossibleMoves[i]);
			}
		}

		uint8_t Complexity = 0;
		uint8_t attempt;
		if (BestMoveList.size() > 1)
		{
			for (size_t i = 0; i < BestMoveList.size(); i++)
			{
				board temp = *this;
				temp.MoveByEngine(BestMoveList[i]);
				attempt = temp.getAllPossibleMovesForEngine().size();
				if (attempt > Complexity)
				{
					Complexity = attempt;
					bestMove = BestMoveList[i];
				}
			}
		}
		return bestMove;
	}

	pair<Loc, Loc> board::findBlackBestMove(int depth) const
	{
		pair<Loc, Loc> bestMove;
		int_fast8_t bestscore = -128;
		vector<pair<Loc, Loc>> allPossibleMoves = getAllPossibleMovesForEngine();
		const int numThreads = allPossibleMoves.size();
		vector<int_fast8_t> bestScoreT = vector<int8_t>(numThreads);
		std::vector<std::thread> threads;
		for (int i = 0; i < numThreads; i++)
		{
			bestScoreT[i] == -128;
			threads.push_back
			(
				std::thread(&board::findBlackBestMoveCore, this, std::ref(allPossibleMoves[i]), std::ref(bestScoreT[i]), depth)
			);
		}
		for (auto& t : threads) {
			t.join();
		}
		bestscore = bestScoreT[0];
		vector<pair<Loc, Loc>> BestMoveList;
		BestMoveList.push_back(allPossibleMoves[0]);
		for (int i = 1; i < numThreads; i++)
		{
			if (bestScoreT[i] > bestscore)
			{
				bestscore = bestScoreT[i];
				BestMoveList.clear();
				BestMoveList.push_back(allPossibleMoves[i]);
			}
			else if (bestScoreT[i] == bestscore)
			{
				BestMoveList.push_back(allPossibleMoves[i]);
			}
		}

		uint8_t Complexity = 0;
		uint8_t attempt;
		if (BestMoveList.size() > 1)
		{
			for (size_t i = 0; i < BestMoveList.size(); i++)
			{
				board temp = *this;
				temp.MoveByEngine(BestMoveList[i]);
				attempt = temp.getAllPossibleMovesForEngine().size();
				if (attempt > Complexity)
				{
					Complexity = attempt;
					bestMove = BestMoveList[i];
				}
			}
		}
		return bestMove;
	}


	void board::findWhiteBestMoveCore(pair<Loc,Loc>& attemptMove, int_fast8_t& bestScoreT,uint8_t depth) const
	{
		assert(isBlackChecked() == false);
		board temp = *this;
		temp.MoveByEngine(attemptMove);
		bestScoreT = -1 * temp.findBlackBestScore(depth - 1);
	}
	void board::findBlackBestMoveCore(pair<Loc, Loc>& attemptMove, int_fast8_t& bestScoreT, uint8_t depth) const
	{
		assert(isBlackChecked() == false);
		board temp = *this;
		temp.MoveByEngine(attemptMove);
		bestScoreT = -1 * temp.findWhiteBestScore(depth - 1);
	}

	int_fast8_t board::findWhiteBestScore(uint8_t depth) const
	{
		assert(player == White);
		if (isBlackChecked())
		{
			return 127;
		}
		if (depth == 0)
		{
			return getWhiteMaterialAdvantage();
		}
		vector<pair<Loc, Loc>> AllPossibleMoves = getAllPossibleMovesForEngine();
		int_fast8_t bestScore = -128;
		int_fast8_t attempt;
		for (pair<Loc, Loc>& move : AllPossibleMoves)
		{
			board temp = *this;
			temp.MoveByEngine(move);
			attempt = -1 * temp.findBlackBestScore(depth - 1);
			if (attempt > bestScore)
			{
				bestScore = attempt;
			}
		}
		return bestScore;
	}

	int_fast8_t board::findBlackBestScore(uint8_t depth) const
	{
		assert(player == Black);
		if (isWhiteChecked())
		{
			return 127;
		}
		if (depth == 0)
		{
			return getBlackMaterialAdvantage();
		}
		vector<pair<Loc, Loc>> AllPossibleMoves = getAllPossibleMovesForEngine();
		int_fast8_t bestScore = -128;
		int_fast8_t attempt;
		for (pair<Loc, Loc>& move : AllPossibleMoves)
		{
			board temp = *this;
			temp.MoveByEngine(move);
			attempt = -1 * temp.findWhiteBestScore(depth - 1);
			if (attempt > bestScore)
			{
				bestScore = attempt;
			}
		}
		return bestScore;
	}

