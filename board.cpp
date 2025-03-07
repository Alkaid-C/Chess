
#include "board.h"
#include "static.cpp"
#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstring>

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
        WhiteCastleKingSideQualified = true;
        WhiteCastleQueenSideQualified = true;
        BlackCastleKingSideQualified = true;
        BlackCastleQueenSideQualified = true;
		LastMove = {};
		mover = White;
    }

	board::board(const board& theboard)
	{
		memcpy(CurBoard, theboard.CurBoard, sizeof(CurBoard));
		TakenPieceBlack = theboard.TakenPieceBlack;
		TakenPieceWhite = theboard.TakenPieceWhite;
		WhiteCastleKingSideQualified = theboard.WhiteCastleKingSideQualified;
		WhiteCastleQueenSideQualified = theboard.WhiteCastleQueenSideQualified;
		BlackCastleKingSideQualified = theboard.BlackCastleKingSideQualified;
		BlackCastleQueenSideQualified = theboard.BlackCastleQueenSideQualified;
		LastMove = theboard.LastMove;
		mover = theboard.mover;
	}


	inline bool board::isLocWhite(Loc loc) const
	{
		return isWhite(CurBoard[loc]);
	}
	inline bool board::isLocBlack(Loc loc) const
	{
		return isBlack(CurBoard[loc]);
	}
	inline bool board::isLocEmpty(Loc loc) const
	{
		return isEmpty(CurBoard[loc]);
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
			for (int_fast8_t i = 7; i >0 ; i--)
			{
				cout << i + 1;
				for (int_fast8_t j = 0; j < 8; j++)
				{
					cout << " ";
					printPiece(CurBoard[i * 8 + j], UnicodeSupported);
				}
				cout << i + 1 << " " << endl;
			}
			cout << "  A B C D E F G H" << endl;
		}
		else
		{
			cout << "  H G F E D C B A" << endl;
			for (int_fast8_t i = 0; i < 8; i++)
			{
				cout << i + 1;
				for (int_fast8_t j = 7; j > 0; j--)
				{
					cout << " ";
					printPiece(CurBoard[i*8+j], UnicodeSupported);
				}
				cout << i + 1 << " " << endl;
			}
			cout << "  H G F E D C B A" << endl;
		}
		if (isBlackCheckmated())
		{
			cout << "White Wins" << endl;
		}
		else if (isWhiteCheckmated())
		{
			cout << "Black Wins" << endl;
		}
		else if (getWhiteMaterialAdvantage() >= 0)
		{
			cout << "White Material Advantage:" << getWhiteMaterialAdvantage() << endl;
		}
		else
		{
			cout << "Black Material Advantage:" << getBlackMaterialAdvantage() << endl;
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
	static inline bool isWhite(const Piece piece)
	{
		return (piece & COLOR_MASK) == Piece::WHITE;
	}
	static inline bool  isBlack(const Piece piece)
	{
		return(piece & COLOR_MASK) == Piece::BLACK;
	}
	static inline bool isEmpty(const Piece piece)
	{
		return piece == Piece::Empty;
	}
	static inline bool isInTheBoard(const Loc loc)
	{
		return loc < 64;
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
		const uint8_t RookDirection[4] = { 1,8,248,255 };
		const uint8_t BishopDirection[4] = { 7,9,247,249 };
		const uint8_t QueenDirection[8] = { 1,7,8,9,247,248,249,255 };
		const uint8_t KnightMoves[8] = { 6,10,15,17,239,241,246,250 };

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
		const uint8_t RookDirection[4] = { 1,8,248,255 };
		const uint8_t BishopDirection[4] = { 7,9,247,249 };
		const uint8_t QueenDirection[8] = { 1,7,8,9,247,248,249,255 };
		const uint8_t KnightMoves[8] = { 6,10,15,17,239,241,246,250 };

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
	bool board::isWhiteChecked() const
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
	bool board::isBlackChecked() const
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
	bool board::willWhiteBeChecked(pair<Loc,Loc> move) const
	{ 
		board NewBoard = *this;
		NewBoard.moveNoCheck(move);
		return NewBoard.isWhiteChecked();
	}
	bool board::willBlackBeChecked(pair<Loc, Loc> move) const
	{
		board NewBoard = *this;
		NewBoard.moveNoCheck(move);
		return NewBoard.isBlackChecked();
	}
	bool board::isWhiteCheckmated() const
	{
		if (!isWhiteChecked())
		{
			return false; 
		}
		else
		{
			vector<Loc> WhitePieces = WhiteOccupiedSquares();
			for (int i = 0; i < WhitePieces.size(); i++)
			{
				vector<pair<int, int>> PossibleMoves = getPossibleMoves(WhitePieces[i].first, WhitePieces[i].second);
				for (int j = 0; j < PossibleMoves.size(); j++)
				{
					if (!willWhiteBeChecked(WhitePieces[i].first, WhitePieces[i].second, PossibleMoves[j].first, PossibleMoves[j].second))
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	bool board::isBlackCheckmated()
	{
		if (!isBlackChecked())
		{
			return false; 
		}
		else
		{
			vector<pair<int, int>> BlackPieces = BlackOccupiedSquares();
			for (int i = 0; i < BlackPieces.size(); i++)
			{
				vector<pair<int, int>> PossibleMoves = getPossibleMoves(BlackPieces[i].first, BlackPieces[i].second);
				for (int j = 0; j < PossibleMoves.size(); j++)
				{
					if (!willBlackBeChecked(BlackPieces[i].first, BlackPieces[i].second, PossibleMoves[j].first, PossibleMoves[j].second))
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	bool board::isWhiteStalemated()
	{
		if (isWhiteChecked())
		{
			return false;
		}
		else
		{
			vector<pair<int, int>> WhitePieces = WhiteOccupiedSquares();
			for (int i = 0; i < WhitePieces.size(); i++)
			{
				vector<pair<int, int>> PossibleMoves = getPossibleMoves(WhitePieces[i].first, WhitePieces[i].second);
				for (int j = 0; j < PossibleMoves.size(); j++)
				{
					board NewBoard = *this;
					NewBoard.move(WhitePieces[i].first, WhitePieces[i].second, PossibleMoves[j].first, PossibleMoves[j].second);
					if (!NewBoard.isWhiteChecked())
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	bool board::isBlackStalemated()
	{
		if (isBlackChecked())
		{
			return false;
		}
		else
		{
			vector<pair<int, int>> BlackPieces = BlackOccupiedSquares();
			for (int i = 0; i < BlackPieces.size(); i++)
			{
				vector<pair<int, int>> PossibleMoves = getPossibleMoves(BlackPieces[i].first, BlackPieces[i].second);
				for (int j = 0; j < PossibleMoves.size(); j++)
				{
					board NewBoard = *this;
					NewBoard.move(BlackPieces[i].first, BlackPieces[i].second, PossibleMoves[j].first, PossibleMoves[j].second);
					if (!NewBoard.isBlackChecked())
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	vector<pair<int, int>> board::getPossibleMoves(int row, int col) const
	{
		bool UpRowOpen;
		bool DownRowOpen;
		bool RightColOpen;
		bool LeftColOpen;
		bool UpRightOpen;
		bool UpLeftOpen;
		bool DownRightOpen;
		bool DownLeftOpen;
		int Index;
		vector<pair<int, int>> result;
		switch (CurBoard[row][col])
		{
		case WhitePawn:
			result.reserve(4);
			if (row == 2) 
			{
				if (CurBoard[4][col] == Empty && CurBoard[3][col]==Empty)
				{
					result.push_back({ 4,col });
				}
			}
			if (row < 8)
			{
				if (CurBoard[row + 1][col] == Empty)
				{
					result.push_back({ row + 1,col });
				}
				if (col+1<9)
				{
					if (isBlack(row + 1, col + 1))
					{
						result.push_back({ row + 1,col + 1 });
					}
				}
				if (col-1>0)
				{
					if (isBlack(row + 1, col - 1))
					{ 
						result.push_back({ row + 1,col - 1 });
					}
				}
			}
			break;
		case WhiteRook:
			result.reserve(14);
			UpRowOpen = true;
			DownRowOpen = true;
			RightColOpen = true;
			LeftColOpen = true;
			Index = row + 1;
			while (UpRowOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index++;
					}
					else if (isWhite(Index, col))
					{
						UpRowOpen = false;
					}
					else//isBlack
					{
						result.push_back({ Index,col });
						UpRowOpen = false;
					}
				}
				else 
				{
					UpRowOpen = false;
				}
			}
			Index = row - 1;
			while (DownRowOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index--;
					}
					else if(isWhite(Index, col))
					{
						DownRowOpen = false;
					} 
					else//isBlack
					{
						result.push_back({ Index,col });
						DownRowOpen = false;
					}				
				}
				else
				{
					DownRowOpen = false;
				}
			}
			Index = col + 1;
			while (RightColOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index++;
					}
					else if (isWhite(row, Index))
					{
						RightColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						RightColOpen = false;
					}
				}
				else
				{
					RightColOpen = false;
				}
			}
			Index = col - 1;
			while (LeftColOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index--;
					}
					else if (isWhite(row, Index))
					{
						LeftColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						LeftColOpen = false;
					}
				}
				else
				{
					LeftColOpen = false;
				}
			}
			break;
		case WhiteKnight:
			result.reserve(8);
			if (isInTheBoard(row + 2, col + 1))
			{
				if (isBlack(row + 2, col + 1) || CurBoard[row + 2][col + 1] == Empty)
				{
					result.push_back({ row + 2,col + 1 });
				}
			}
			if (isInTheBoard(row + 2, col - 1))
			{
				if (isBlack(row + 2, col - 1) || CurBoard[row + 2][col - 1] == Empty)
				{
					result.push_back({ row + 2,col - 1 });
				}
			}
			if (isInTheBoard(row - 2, col + 1))
			{
				if (isBlack(row - 2, col + 1) || CurBoard[row - 2][col + 1] == Empty)
				{
					result.push_back({ row - 2,col + 1 });
				}
			}
			if (isInTheBoard(row - 2, col - 1))
			{
				if (isBlack(row - 2, col - 1) || CurBoard[row - 2][col - 1] == Empty)
				{
					result.push_back({ row - 2,col - 1 });
				}
			}
			if (isInTheBoard(row + 1, col + 2))
			{
				if (isBlack(row + 1, col + 2) || CurBoard[row + 1][col + 2] == Empty)
				{
					result.push_back({ row + 1,col + 2 });
				}
			}
			if (isInTheBoard(row + 1, col - 2))
			{
				if (isBlack(row + 1, col - 2) || CurBoard[row + 1][col - 2] == Empty)
				{
					result.push_back({ row + 1,col - 2 });
				}
			}
			if (isInTheBoard(row - 1, col + 2))
			{
				if (isBlack(row - 1, col + 2) || CurBoard[row - 1][col + 2] == Empty)
				{
					result.push_back({ row - 1,col + 2 });
				}
			}
			if (isInTheBoard(row - 1, col - 2))
			{
				if (isBlack(row - 1, col - 2) || CurBoard[row - 1][col - 2] == Empty)
				{
					result.push_back({ row - 1,col - 2 });
				}
			}
			break;
		case WhiteBishop:
			result.reserve(14);
			UpRightOpen = true;
			UpLeftOpen = true;
			DownRightOpen = true;
			DownLeftOpen = true;
			Index = 1;
			while (UpRightOpen)
			{
				if (isInTheBoard(row + Index, col + Index))
				{
					if (CurBoard[row + Index][col + Index] == Empty)
					{
						result.push_back({ row + Index,col + Index });
						Index++;
					}
					else if (isWhite(row + Index, col + Index))
					{
						UpRightOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col + Index });
						UpRightOpen = false;
					}
				}
				else
				{
					UpRightOpen = false;
				}
			}
			Index = 1;
			while (UpLeftOpen)
			{
				if (isInTheBoard(row + Index, col - Index))
				{
					if (CurBoard[row + Index][col - Index] == Empty)
					{
						result.push_back({ row + Index,col - Index });
						Index++;
					}
					else if (isWhite(row + Index, col - Index))
					{
						UpLeftOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col - Index });
						UpLeftOpen = false;
					}
				}
				else
				{
					UpLeftOpen = false;
				}
			}
			Index = 1;
			while (DownRightOpen)
			{
				if (isInTheBoard(row - Index, col + Index))
				{
					if (CurBoard[row - Index][col + Index] == Empty)
					{
						result.push_back({ row - Index,col + Index });
						Index++;
					}
					else if (isWhite(row - Index, col + Index))
					{
						DownRightOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col + Index });
						DownRightOpen = false;
					}
				}
				else
				{
					DownRightOpen = false;
				}
			}
			Index = 1;
			while (DownLeftOpen)
			{
				if (isInTheBoard(row - Index, col - Index))
				{
					if (CurBoard[row - Index][col - Index] == Empty)
					{
						result.push_back({ row - Index,col - Index });
						Index++;
					}
					else if (isWhite(row - Index, col - Index))
					{
						DownLeftOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col - Index });
						DownLeftOpen = false;
					}
				}
				else
				{
					DownLeftOpen = false;
				}
			}
			break;
		case WhiteQueen:
			result.reserve(28);
			UpRowOpen = true;
			DownRowOpen = true;
			RightColOpen = true;
			LeftColOpen = true;
			Index = row + 1;
			while (UpRowOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index++;
					}
					else if (isWhite(Index, col))
					{
						UpRowOpen = false;
					}
					else
					{
						result.push_back({ Index,col });
						UpRowOpen = false;
					}
				}
				else
				{
					UpRowOpen = false;
				}
			}
			Index = row - 1;
			while (DownRowOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index--;
					}
					else if (isWhite(Index, col))
					{
						DownRowOpen = false;
					}
					else
					{
						result.push_back({ Index,col });
						DownRowOpen = false;
					}
				}
				else
				{
					DownRowOpen = false;
				}
			}
			Index = col + 1;
			while (RightColOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index++;
					}
					else if (isWhite(row, Index))
					{
						RightColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						RightColOpen = false;
					}
				}
				else
				{
					RightColOpen = false;
				}
			}
			Index = col - 1;
			while (LeftColOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index--;
					}
					else if (isWhite(row, Index))
					{
						LeftColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						LeftColOpen = false;
					}
				}
				else
				{
					LeftColOpen = false;
				}
			}
			UpRightOpen = true;
			UpLeftOpen = true;
			DownRightOpen = true;
			DownLeftOpen = true;
			Index = 1;
			while (UpRightOpen)
			{
				if (isInTheBoard(row + Index, col + Index))
				{
					if (CurBoard[row + Index][col + Index] == Empty)
					{
						result.push_back({ row + Index,col + Index });
						Index++;
					}
					else if (isWhite(row + Index, col + Index))
					{
						UpRightOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col + Index });
						UpRightOpen = false;
					}
				}
				else
				{
					UpRightOpen = false;
				}
			}
			Index = 1;
			while (UpLeftOpen)
			{
				if (isInTheBoard(row + Index, col - Index))
				{
					if (CurBoard[row + Index][col - Index] == Empty)
					{
						result.push_back({ row + Index,col - Index });
						Index++;
					}
					else if (isWhite(row + Index, col - Index))
					{
						UpLeftOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col - Index });
						UpLeftOpen = false;
					}
				}
				else
				{
					UpLeftOpen = false;
				}
			}
			Index = 1;
			while (DownRightOpen)
			{
				if (isInTheBoard(row - Index, col + Index))
				{
					if (CurBoard[row - Index][col + Index] == Empty)
					{
						result.push_back({ row - Index,col + Index });
						Index++;
					}
					else if (isWhite(row - Index, col + Index))
					{
						DownRightOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col + Index });
						DownRightOpen = false;
					}
				}
				else
				{
					DownRightOpen = false;
				}
			}
			Index = 1;
			while (DownLeftOpen)
			{
				if (isInTheBoard(row - Index, col - Index))
				{
					if (CurBoard[row - Index][col - Index] == Empty)
					{
						result.push_back({ row - Index,col - Index });
						Index++;
					}
					else if (isWhite(row - Index, col - Index))
					{
						DownLeftOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col - Index });
						DownLeftOpen = false;
					}
				}
				else
				{
					DownLeftOpen = false;
				}
			}
			break;
		case WhiteKing:
			result.reserve(8);
			if (isInTheBoard(row + 1, col))
			{
				if (isBlack(row + 1, col) || CurBoard[row + 1][col] == Empty)
				{
					result.push_back({ row + 1,col });
				}
			}
			if (isInTheBoard(row - 1, col))
			{
				if (isBlack(row - 1, col) || CurBoard[row - 1][col] == Empty)
				{
					result.push_back({ row - 1,col });
				}
			}
			if (isInTheBoard(row, col + 1))
			{
				if (isBlack(row, col + 1) || CurBoard[row][col + 1] == Empty)
				{
					result.push_back({ row,col + 1 });
				}
			}
			if (isInTheBoard(row, col - 1))
			{
				if (isBlack(row, col - 1) || CurBoard[row][col - 1] == Empty)
				{
					result.push_back({ row,col - 1 });
				}
			}
			if (isInTheBoard(row + 1, col + 1))
			{
				if (isBlack(row + 1, col + 1) || CurBoard[row + 1][col + 1] == Empty)
				{
					result.push_back({ row + 1,col + 1 });
				}
			}
			if (isInTheBoard(row + 1, col - 1))
			{
				if (isBlack(row + 1, col - 1) || CurBoard[row + 1][col - 1] == Empty)
				{
					result.push_back({ row + 1,col - 1 });
				}
			}
			if (isInTheBoard(row - 1, col + 1))
			{
				if (isBlack(row - 1, col + 1) || CurBoard[row - 1][col + 1] == Empty)
				{
					result.push_back({ row - 1,col + 1 });
				}
			}
			if (isInTheBoard(row - 1, col - 1))
			{
				if (isBlack(row - 1, col - 1) || CurBoard[row - 1][col - 1] == Empty)
				{
					result.push_back({ row - 1,col - 1 });
				}
			}
			break;
		case BlackPawn:
			result.reserve(4);
			if (row == 7)
			{
				if (CurBoard[5][col] == Empty && CurBoard[6][col]==Empty)
				{
					result.push_back({ 5,col });
				}
			}
			if (row > 1)
			{
				if (CurBoard[row - 1][col] == Empty)
				{
					result.push_back({ row - 1,col });
				}
				if (col + 1 < 9)
				{
					if (isWhite(row - 1, col + 1))
					{
						result.push_back({ row - 1,col + 1 });
					}
				}
				if (col - 1 > 0)
				{
					if (isWhite(row - 1, col - 1))
					{
						result.push_back({ row - 1,col - 1 });
					}
				}
			}
			break;
		case BlackRook:
			result.reserve(14);
			UpRowOpen = true;
			DownRowOpen = true;
			RightColOpen = true;
			LeftColOpen = true;
			Index = row + 1;
			while (UpRowOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index++;
					}
					else if (isBlack(Index, col))
					{
						UpRowOpen = false;
					}
					else//isWhite
					{
						result.push_back({ Index,col });
						UpRowOpen = false;
					}
				}
				else
				{
					UpRowOpen = false;
				}
			}
			Index = row - 1;
			while (DownRowOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index--;
					}
					else if (isBlack(Index, col))
					{
						DownRowOpen = false;
					}
					else//isWhite
					{
						result.push_back({ Index,col });
						DownRowOpen = false;
					}
				}
				else
				{
					DownRowOpen = false;
				}
			}
			Index = col + 1;
			while (RightColOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index++;
					}
					else if (isBlack(row, Index))
					{
						RightColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						RightColOpen = false;
					}
				}
				else
				{
					RightColOpen = false;
				}
			}
			Index = col - 1;
			while (LeftColOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index--;
					}
					else if (isBlack(row, Index))
					{
						LeftColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						LeftColOpen = false;
					}
				}
				else
				{
					LeftColOpen = false;
				}
			}
			break;
		case BlackKnight:
			result.reserve(8);
			if (isInTheBoard(row + 2, col + 1))
			{
				if (isWhite(row + 2, col + 1) || CurBoard[row + 2][col + 1] == Empty)
				{
					result.push_back({ row + 2,col + 1 });
				}
			}
			if (isInTheBoard(row + 2, col - 1))
			{
				if (isWhite(row + 2, col - 1) || CurBoard[row + 2][col - 1] == Empty)
				{
					result.push_back({ row + 2,col - 1 });
				}
			}
			if (isInTheBoard(row - 2, col + 1))
			{
				if (isWhite(row - 2, col + 1) || CurBoard[row - 2][col + 1] == Empty)
				{
					result.push_back({ row - 2,col + 1 });
				}
			}
			if (isInTheBoard(row - 2, col - 1))
			{
				if (isWhite(row - 2, col - 1) || CurBoard[row - 2][col - 1] == Empty)
				{
					result.push_back({ row - 2,col - 1 });
				}
			}
			if (isInTheBoard(row + 1, col + 2))
			{
				if (isWhite(row + 1, col + 2) || CurBoard[row + 1][col + 2] == Empty)
				{
					result.push_back({ row + 1,col + 2 });
				}
			}
			if (isInTheBoard(row + 1, col - 2))
			{
				if (isWhite(row + 1, col - 2) || CurBoard[row + 1][col - 2] == Empty)
				{
					result.push_back({ row + 1,col - 2 });
				}
			}
			if (isInTheBoard(row - 1, col + 2))
			{
				if (isWhite(row - 1, col + 2) || CurBoard[row - 1][col + 2] == Empty)
				{
					result.push_back({ row - 1,col + 2 });
				}
			}
			if (isInTheBoard(row - 1, col - 2))
			{
				if (isWhite(row - 1, col - 2) || CurBoard[row - 1][col - 2] == Empty)
				{
					result.push_back({ row - 1,col - 2 });
				}
			}
			break;
		case BlackBishop:
			result.reserve(14);
			UpRightOpen = true;
			UpLeftOpen = true;
			DownRightOpen = true;
			DownLeftOpen = true;
			Index = 1;
			while (UpRightOpen)
			{
				if (isInTheBoard(row + Index, col + Index))
				{
					if (CurBoard[row + Index][col + Index] == Empty)
					{
						result.push_back({ row + Index,col + Index });
						Index++;
					}
					else if (isBlack(row + Index, col + Index))
					{
						UpRightOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col + Index });
						UpRightOpen = false;
					}
				}
				else
				{
					UpRightOpen = false;
				}
			}
			Index = 1;
			while (UpLeftOpen)
			{
				if (isInTheBoard(row + Index, col - Index))
				{
					if (CurBoard[row + Index][col - Index] == Empty)
					{
						result.push_back({ row + Index,col - Index });
						Index++;
					}
					else if (isBlack(row + Index, col - Index))
					{
						UpLeftOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col - Index });
						UpLeftOpen = false;
					}
				}
				else
				{
					UpLeftOpen = false;
				}
			}
			Index = 1;
			while (DownRightOpen)
			{
				if (isInTheBoard(row - Index, col + Index))
				{
					if (CurBoard[row - Index][col + Index] == Empty)
					{
						result.push_back({ row - Index,col + Index });
						Index++;
					}
					else if (isBlack(row - Index, col + Index))
					{
						DownRightOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col + Index });
						DownRightOpen = false;
					}
				}
				else
				{
					DownRightOpen = false;
				}
			}
			Index = 1;
			while (DownLeftOpen)
			{
				if (isInTheBoard(row - Index, col - Index))
				{
					if (CurBoard[row - Index][col - Index] == Empty)
					{
						result.push_back({ row - Index,col - Index });
						Index++;
					}
					else if (isBlack(row - Index, col - Index))
					{
						DownLeftOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col - Index });
						DownLeftOpen = false;
					}
				}
				else
				{
					DownLeftOpen = false;
				}
			}
			break;
		case BlackQueen:
			result.reserve(28);
			UpRowOpen = true;
			DownRowOpen = true;
			RightColOpen = true;
			LeftColOpen = true;
			Index = row + 1;
			while (UpRowOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index++;
					}
					else if (isBlack(Index, col))
					{
						UpRowOpen = false;
					}
					else
					{
						result.push_back({ Index,col });
						UpRowOpen = false;
					}
				}
				else
				{
					UpRowOpen = false;
				}
			}
			Index = row - 1;
			while (DownRowOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[Index][col] == Empty)
					{
						result.push_back({ Index,col });
						Index--;
					}
					else if (isBlack(Index, col))
					{
						DownRowOpen = false;
					}
					else
					{
						result.push_back({ Index,col });
						DownRowOpen = false;
					}
				}
				else
				{
					DownRowOpen = false;
				}
			}
			Index = col + 1;
			while (RightColOpen)
			{
				if (Index < 9)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index++;
					}
					else if (isBlack(row, Index))
					{
						RightColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						RightColOpen = false;
					}
				}
				else
				{
					RightColOpen = false;
				}
			}
			Index = col - 1;
			while (LeftColOpen)
			{
				if (Index > 0)
				{
					if (CurBoard[row][Index] == Empty)
					{
						result.push_back({ row,Index });
						Index--;
					}
					else if (isBlack(row, Index))
					{
						LeftColOpen = false;
					}
					else
					{
						result.push_back({ row,Index });
						LeftColOpen = false;
					}
				}
				else
				{
					LeftColOpen = false;
				}
			}
			UpRightOpen = true;
			UpLeftOpen = true;
			DownRightOpen = true;
			DownLeftOpen = true;
			Index = 1;
			while (UpRightOpen)
			{
				if (isInTheBoard(row + Index, col + Index))
				{
					if (CurBoard[row + Index][col + Index] == Empty)
					{
						result.push_back({ row + Index,col + Index });
						Index++;
					}
					else if (isBlack(row + Index, col + Index))
					{
						UpRightOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col + Index });
						UpRightOpen = false;
					}
				}
				else
				{
					UpRightOpen = false;
				}
			}
			Index = 1;
			while (UpLeftOpen)
			{
				if (isInTheBoard(row + Index, col - Index))
				{
					if (CurBoard[row + Index][col - Index] == Empty)
					{
						result.push_back({ row + Index,col - Index });
						Index++;
					}
					else if (isBlack(row + Index, col - Index))
					{
						UpLeftOpen = false;
					}
					else
					{
						result.push_back({ row + Index,col - Index });
						UpLeftOpen = false;
					}
				}
				else
				{
					UpLeftOpen = false;
				}
			}
			Index = 1;
			while (DownRightOpen)
			{
				if (isInTheBoard(row - Index, col + Index))
				{
					if (CurBoard[row - Index][col + Index] == Empty)
					{
						result.push_back({ row - Index,col + Index });
						Index++;
					}
					else if (isBlack(row - Index, col + Index))
					{
						DownRightOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col + Index });
						DownRightOpen = false;
					}
				}
				else
				{
					DownRightOpen = false;
				}
			}
			Index = 1;
			while (DownLeftOpen)
			{
				if (isInTheBoard(row - Index, col - Index))
				{
					if (CurBoard[row - Index][col - Index] == Empty)
					{
						result.push_back({ row - Index,col - Index });
						Index++;
					}
					else if (isBlack(row - Index, col - Index))
					{
						DownLeftOpen = false;
					}
					else
					{
						result.push_back({ row - Index,col - Index });
						DownLeftOpen = false;
					}
				}
				else
				{
					DownLeftOpen = false;
				}
			}
			break;
		case BlackKing:
			result.reserve(8);
			if (isInTheBoard(row + 1, col))
			{
				if (isWhite(row + 1, col) || CurBoard[row + 1][col] == Empty)
				{
					result.push_back({ row + 1,col });
				}
			}
			if (isInTheBoard(row - 1, col))
			{
				if (isWhite(row - 1, col) || CurBoard[row - 1][col] == Empty)
				{
					result.push_back({ row - 1,col });
				}
			}
			if (isInTheBoard(row, col + 1))
			{
				if (isWhite(row, col + 1) || CurBoard[row][col + 1] == Empty)
				{
					result.push_back({ row,col + 1 });
				}
			}
			if (isInTheBoard(row, col - 1))
			{
				if (isWhite(row, col - 1) || CurBoard[row][col - 1] == Empty)
				{
					result.push_back({ row,col - 1 });
				}
			}
			if (isInTheBoard(row + 1, col + 1))
			{
				if (isWhite(row + 1, col + 1) || CurBoard[row + 1][col + 1] == Empty)
				{
					result.push_back({ row + 1,col + 1 });
				}
			}
			if (isInTheBoard(row + 1, col - 1))
			{
				if (isWhite(row + 1, col - 1) || CurBoard[row + 1][col - 1] == Empty)
				{
					result.push_back({ row + 1,col - 1 });
				}
			}
			if (isInTheBoard(row - 1, col + 1))
			{
				if (isWhite(row - 1, col + 1) || CurBoard[row - 1][col + 1] == Empty)
				{
					result.push_back({ row - 1,col + 1 });
				}
			}
			if (isInTheBoard(row - 1, col - 1))
			{
				if (isWhite(row - 1, col - 1) || CurBoard[row - 1][col - 1] == Empty)
				{
					result.push_back({ row - 1,col - 1 });
				}
			}
			break;
		}
		if (mover == White)
		{
			for (int i = 0; i < result.size(); i++)
			{
				if (willWhiteBeChecked(row, col, result[i].first, result[i].second))
				{
					result.erase(result.begin() + i);
					i--;
				}
			}
		}
		else
		{
			for (int i = 0; i < result.size(); i++)
			{
				if (willBlackBeChecked(row, col, result[i].first, result[i].second))
				{
					result.erase(result.begin() + i);
					i--;
				}
			}
		}
		return result;
	}
	vector<pair<int, int>> board::getPossibleEnPassant(int row, int col) const
	{
		vector<pair<int, int>> result;
		if (row == 5 && CurBoard[row][col]==WhitePawn)
		{
			if (col + 1 < 9)
			{
				if (CurBoard[5][col + 1] == BlackPawn)
				{
					if (MoveHistory[MoveHistory.size() - 1].first.first == 7 && MoveHistory[MoveHistory.size() - 1].first.second == col + 1 && MoveHistory[MoveHistory.size() - 1].second.first == 5 && MoveHistory[MoveHistory.size() - 1].second.second == col + 1)
					{
						result.push_back({ 6,col + 1 });
					}

				}
			}
			if (col - 1 > 0)
			{
				if (CurBoard[5][col - 1] == BlackPawn)
				{
					if (MoveHistory[MoveHistory.size() - 1].first.first == 7 && MoveHistory[MoveHistory.size() - 1].first.second == col - 1 && MoveHistory[MoveHistory.size() - 1].second.first == 5 && MoveHistory[MoveHistory.size() - 1].second.second == col - 1)
					{
						result.push_back({ 6,col - 1 });
					}
				}
			}
		}
		else if (row == 4 && CurBoard[row][col] == BlackPawn)
		{
			if (col + 1 < 9)
			{
				if (CurBoard[4][col + 1] == WhitePawn)
				{
					if (MoveHistory[MoveHistory.size() - 1].first.first == 2 && MoveHistory[MoveHistory.size() - 1].first.second == col + 1 && MoveHistory[MoveHistory.size() - 1].second.first == 4 && MoveHistory[MoveHistory.size() - 1].second.second == col + 1)
					{
						result.push_back({ 3,col + 1 });
					}
				}
			}
			if (col - 1 > 0)
			{
				if (CurBoard[4][col - 1] == WhitePawn)
				{
					if (MoveHistory[MoveHistory.size() - 1].first.first == 2 && MoveHistory[MoveHistory.size() - 1].first.second == col - 1 && MoveHistory[MoveHistory.size() - 1].second.first == 4 && MoveHistory[MoveHistory.size() - 1].second.second == col - 1)
					{
						result.push_back({ 3,col - 1 });
					}
				}
			}
		}
		return result;
	}
	vector<pair<int, int>> board::getPossibleCastling(int row, int col) const
	{
		vector<pair<int, int>> result;
		if (CurBoard[row][col] == WhiteKing)
		{
			if (WhiteCastleKingSideQualified)
			{
				if (CurBoard[1][F] == Empty && CurBoard[1][G] == Empty && CurBoard[1][H] == WhiteRook && !isBlackControlled(1, E) && !isBlackControlled(1, F) && !isBlackControlled(1, G))
				{
					result.push_back({ 1,G });
				}
			}
			if (WhiteCastleQueenSideQualified)
			{
				if (CurBoard[1][B] == Empty && CurBoard[1][C] == Empty && CurBoard[1][D] == Empty && CurBoard[1][A] == WhiteRook && !isBlackControlled(1, E) && !isBlackControlled(1, D) && !isBlackControlled(1, C))
				{
						result.push_back({ 1,C });
				}
			}
		}
		else if (CurBoard[row][col] == BlackKing)
		{

			if (BlackCastleKingSideQualified)
			{
				if (CurBoard[8][F] == Empty && CurBoard[8][G] == Empty && CurBoard[8][H] == BlackRook && !isWhiteControlled(8, E) && !isWhiteControlled(8, F) && !isWhiteControlled(8, G))
				{
					result.push_back({ 8,G });
				}
			}
			if (BlackCastleQueenSideQualified)
			{

				if (CurBoard[8][B] == Empty && CurBoard[8][C] == Empty && CurBoard[8][D] == Empty && CurBoard[8][A] == BlackRook && !isWhiteControlled(8, E) && !isWhiteControlled(8, D) && !isWhiteControlled(8, C))
				{

					result.push_back({ 8,C });
				}
			}
		}
		return result;
	}
	vector<pair<pair<int, int>, pair<int, int>>> board::getAllWhitePossibleMoves() const
	{
		vector<pair<pair<int, int>, pair<int, int>>> result;
		result.reserve(128); 
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 9; j++)
			{
				if (isWhite(i, j))
				{
					const pair<int, int> from(i, j);
					const vector<pair<int, int>> possibleMoves = getPossibleMoves(i, j);
					for (size_t k = 0; k < possibleMoves.size(); k++)
					{
						result.emplace_back(from, possibleMoves[k]);
					}
					const vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(i, j);
					for (size_t k = 0; k < possibleEnPassant.size(); k++)
					{
						result.emplace_back(from, possibleEnPassant[k]);
					}
					const vector<pair<int, int>> possibleCastling = getPossibleCastling(i, j);
					for (size_t k = 0; k < possibleCastling.size(); k++)
					{
						result.emplace_back(from, possibleCastling[k]);
					}
				}
			}
		}

		return result;
	}
	vector<pair<pair < int, int>, pair<int, int>> > board::getAllBlackPossibleMoves() const
	{
		vector<pair<pair < int, int>, pair<int, int>> > result;
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 9; j++)
			{
				if (isBlack(i, j))
				{
					const pair<int, int> from(i, j);
					const vector<pair<int, int>> possibleMoves = getPossibleMoves(i, j);
					for (size_t k = 0; k < possibleMoves.size(); k++)
					{
						result.emplace_back(from, possibleMoves[k]);
					}
					const vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(i, j);
					for (size_t k = 0; k < possibleEnPassant.size(); k++)
					{
						result.emplace_back(from, possibleEnPassant[k]);
					}
					const vector<pair<int, int>> possibleCastling = getPossibleCastling(i, j);
					for (size_t k = 0; k < possibleCastling.size(); k++)
					{
						result.emplace_back(from, possibleCastling[k]);
					}
				}
			}
		}
		return result;
	}
	bool board::move(int row, int col, int newRow, int newCol)
	{
		const vector<pair<int, int>> possibleMoves = getPossibleMoves(row, col);
		bool isRegularMove = false;
		for (int i = 0; i < possibleMoves.size(); i++)
		{
			if (possibleMoves[i].first == newRow && possibleMoves[i].second == newCol)
			{
				isRegularMove = true;
			}
		}
		if (isRegularMove)
		{
			if (isWhite(newRow, newCol))
			{
				TakenPieceWhite.push_back(CurBoard[newRow][newCol]);
			}
			else if (isBlack(newRow,newCol))
			{
				TakenPieceBlack.push_back(CurBoard[newRow][newCol]);
			}
			if (WhiteCastleKingSideQualified || WhiteCastleQueenSideQualified || BlackCastleKingSideQualified || BlackCastleQueenSideQualified)
			{
				switch (CurBoard[row][col])
				{
				case WhiteKing:
					WhiteCastleKingSideQualified = false;
					WhiteCastleQueenSideQualified = false;
					break;
				case WhiteRook:
					if (row == 1 && col == A)
					{
						WhiteCastleQueenSideQualified = false;
					}
					else if (row == 1 && col == H)
					{
						WhiteCastleKingSideQualified = false;
					}
					break;
				case BlackKing:
					BlackCastleKingSideQualified = false;
					BlackCastleQueenSideQualified = false;
					break;
				case BlackRook:
					if (row == 8 && col == A)
					{
						BlackCastleQueenSideQualified = false;
					}
					else if (row == 8 && col == H)
					{
						BlackCastleKingSideQualified = false;
					}
					break;
				}
			}
			CurBoard[newRow][newCol] = CurBoard[row][col];
			CurBoard[row][col] = Empty;
		}
		else
		{
			const vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(row, col);
			bool isEnPassant = false;
			for (int i = 0; i < possibleEnPassant.size(); i++)
			{
				if (possibleEnPassant[i].first == newRow && possibleEnPassant[i].second == newCol)
				{
					isEnPassant = true;
				}
			}
			if (isEnPassant)
			{
				CurBoard[newRow][newCol] = CurBoard[row][col];
				CurBoard[row][col] = Empty;
				if (CurBoard[newRow][newCol] == WhitePawn)
				{
					CurBoard[newRow - 1][newCol] = Empty;
					TakenPieceBlack.push_back(BlackPawn);
				}
				else
				{
					CurBoard[newRow + 1][newCol] = Empty;
					TakenPieceWhite.push_back(WhitePawn);
				}
			}
			else
			{
				const vector<pair<int, int>> possibleCastling = getPossibleCastling(row, col);
				bool isCastling = false;
				for (int i = 0; i < possibleCastling.size(); i++)
				{
					if (possibleCastling[i].first == newRow && possibleCastling[i].second == newCol)
					{
						isCastling = true;
					}
				}
				if (isCastling)
				{
					CurBoard[newRow][newCol] = CurBoard[row][col];
					CurBoard[row][col] = Empty;
					if (newCol == C)
					{
						CurBoard[newRow][newCol + 1] = CurBoard[newRow][A];
						CurBoard[newRow][1] = Empty;
					}
					else
					{
						CurBoard[newRow][newCol - 1] = CurBoard[newRow][H];
						CurBoard[newRow][8] = Empty;
					}
				}
				else
				{
					cout << "Invalid Move" << endl;
					return false;
				}
			}
		}
		mover = !mover;
		MoveHistory.push_back({ {row,col},{newRow,newCol} });
		return true;
	}
	void board::moveNoCheck(int row, int col, int newRow, int newCol)
	{
		const vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(row, col);
		bool isEnPassant = false;
		for (int i = 0; i < possibleEnPassant.size(); i++)
		{
			if (possibleEnPassant[i].first == newRow && possibleEnPassant[i].second == newCol)
			{
				isEnPassant = true;
			}
		}
		if (isEnPassant)
		{
			CurBoard[newRow][newCol] = CurBoard[row][col];
			CurBoard[row][col] = Empty;
			if (CurBoard[newRow][newCol] == WhitePawn)
			{
				CurBoard[newRow - 1][newCol] = Empty;
				TakenPieceBlack.push_back(BlackPawn);
			}
			else
			{
				CurBoard[newRow + 1][newCol] = Empty;
				TakenPieceWhite.push_back(WhitePawn);
			}
		}
		else
		{
			const vector<pair<int, int>> possibleCastling = getPossibleCastling(row, col);
			bool isCastling = false;
			for (int i = 0; i < possibleCastling.size(); i++)
			{
				if (possibleCastling[i].first == newRow && possibleCastling[i].second == newCol)
				{
					isCastling = true;
				}
			}
			if (isCastling)
			{
				CurBoard[newRow][newCol] = CurBoard[row][col];
				CurBoard[row][col] = Empty;
				if (newCol == C)
				{
					CurBoard[newRow][newCol + 1] = CurBoard[newRow][A];
					CurBoard[newRow][1] = Empty;
				}
				else
				{
					CurBoard[newRow][newCol - 1] = CurBoard[newRow][H];
					CurBoard[newRow][8] = Empty;
				}
			}
			else
			{
				if (isWhite(newRow, newCol))
				{
					TakenPieceWhite.push_back(CurBoard[newRow][newCol]);
				}
				else if (isBlack(newRow, newCol))
				{
					TakenPieceBlack.push_back(CurBoard[newRow][newCol]);
				}
				if (WhiteCastleKingSideQualified || WhiteCastleQueenSideQualified || BlackCastleKingSideQualified || BlackCastleQueenSideQualified)
				{
					switch (CurBoard[row][col])
					{
					case WhiteKing:
						WhiteCastleKingSideQualified = false;
						WhiteCastleQueenSideQualified = false;
						break;
					case WhiteRook:
						if (row == 1 && col == A)
						{
							WhiteCastleQueenSideQualified = false;
						}
						else if (row == 1 && col == H)
						{
							WhiteCastleKingSideQualified = false;
						}
						break;
					case BlackKing:
						BlackCastleKingSideQualified = false;
						BlackCastleQueenSideQualified = false;
						break;
					case BlackRook:
						if (row == 8 && col == A)
						{
							BlackCastleQueenSideQualified = false;
						}
						else if (row == 8 && col == H)
						{
							BlackCastleKingSideQualified = false;
						}
						break;
					}
				}
				CurBoard[newRow][newCol] = CurBoard[row][col];
				CurBoard[row][col] = Empty;
			}
		}
		MoveHistory.push_back({ {row,col},{newRow,newCol} });
		mover = !mover;
		return;
	}
	pair<pair<pair<int, int>, pair<int, int>>, int> board::findWhiteBestMove(int depth)
	{
		pair<pair<int, int>, pair<int, int>> bestMove;
		int bestscore = -100000;
		vector<pair<pair < int, int>, pair<int, int>> > allPossibleMoves = getAllWhitePossibleMoves();
		int numThreads = allPossibleMoves.size();
		vector<pair<pair<int, int>, pair<int, int>>> BestMoveT = vector<pair<pair<int, int>, pair<int, int>>>(numThreads);
		vector<int> bestScoreT = vector<int>(numThreads);
		std::vector<std::thread> threads;
		for (int i = 0; i < numThreads; i++) 
		{

			threads.push_back
			(
				std::thread(&board::findBlackBestMoveCore, this, std::ref(BestMoveT[i]), std::ref(bestScoreT[i]), std::ref(allPossibleMoves), i, i + 1, depth)
			);
			
		}
		bestscore = bestScoreT[0];
		vector<pair<pair<int, int>, pair<int, int>>> BestMoveList;
		BestMoveList.push_back(BestMoveT[0]);
		for (int i = 1; i < numThreads; i++)
		{
			if (bestScoreT[i] > bestscore) 
			{
				bestscore = bestScoreT[i];
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT[i]);
			}
			else if (bestScoreT[i] == bestscore) 
			{
				BestMoveList.push_back(BestMoveT[i]);
			}
		}
		for (auto& t : threads) {
			t.join();
		}
		int Complexity = 0;
		int attempt;
		if (BestMoveList.size() > 1)
		{
			for (int i = 0; i < BestMoveList.size(); i++)
			{
				board temp = *this;
				temp.moveNoCheck(BestMoveList[i].first.first, BestMoveList[i].first.second, BestMoveList[i].second.first, BestMoveList[i].second.first);
				attempt = temp.getAllBlackPossibleMoves().size();
				if (attempt > Complexity)
				{
					Complexity = attempt;
					bestMove = BestMoveList[i];
				}
			}
		}
		return { bestMove, bestscore };
	}
	pair<pair<pair<int, int>, pair<int, int>>, int> board::findBlackBestMove(int depth)
	{
		pair<pair<int, int>, pair<int, int>> bestMove;
		int bestscore = -100000;
		vector<pair<pair < int, int>, pair<int, int>> > allPossibleMoves = getAllBlackPossibleMoves();
		int numThreads = allPossibleMoves.size();
		vector<pair<pair<int, int>, pair<int, int>>> BestMoveT = vector<pair<pair<int, int>, pair<int, int>>>(numThreads);
		vector<int> bestScoreT = vector<int>(numThreads);
		std::vector<std::thread> threads;
		for (int i = 0; i < numThreads; i++)
		{

			threads.push_back
			(
				std::thread(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT[i]), std::ref(bestScoreT[i]), std::ref(allPossibleMoves), i, i + 1, depth)
			);

		}
		bestscore = bestScoreT[0];
		vector<pair<pair<int, int>, pair<int, int>>> BestMoveList;
		BestMoveList.push_back(BestMoveT[0]);
		for (int i = 1; i < numThreads; i++)
		{
			if (bestScoreT[i] > bestscore)
			{
				bestscore = bestScoreT[i];
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT[i]);
			}
			else if (bestScoreT[i] == bestscore)
			{
				BestMoveList.push_back(BestMoveT[i]);
			}
		}
		for (auto& t : threads) {
			t.join();
		}
		int Complexity = 0;
		int attempt;
		if (BestMoveList.size() > 1)
		{
			for (int i = 0; i < BestMoveList.size(); i++)
			{
				board temp = *this;
				temp.moveNoCheck(BestMoveList[i].first.first, BestMoveList[i].first.second, BestMoveList[i].second.first, BestMoveList[i].second.first);
				attempt = temp.getAllWhitePossibleMoves().size();
				if (attempt > Complexity)
				{
					Complexity = attempt;
					bestMove = BestMoveList[i];
					
				}
			}
		}
		return { bestMove, bestscore };
	}
	int board::findWhiteBestScore(int depth)
	{
		if (depth == 0) 
		{
			return getWhiteMaterialAdvantage();
		}
		if (isBlackCheckmated())
		{
			return 100000;
		}
		if (isWhiteCheckmated())
		{
			return -100000;
		}
		const vector<pair<pair<int, int>, pair<int, int>>> allPossibleMoves = getAllWhitePossibleMoves();
		int bestScore = -100000;
		int attempt;
		for (const pair<pair<int, int>, pair<int, int>> move : allPossibleMoves)
		{
			board temp = *this;
			temp.moveNoCheck(move.first.first, move.first.second, move.second.first, move.second.second);
			attempt = -1 * temp.findBlackBestScore(depth - 1);
			if (attempt > bestScore)
			{
				bestScore = attempt;
			}
		}
		return bestScore;
	}
	int board::findBlackBestScore(int depth) 
	{
		if (depth == 0)
		{
			return getWhiteMaterialAdvantage();
		}
		if (isWhiteCheckmated())
		{
			return 100000;
		}
		if (isBlackCheckmated())
		{
			return -100000;
		}
		const vector<pair<pair<int, int>, pair<int, int>>> allPossibleMoves = getAllBlackPossibleMoves();
		int bestScore = -100000;
		int attempt;
		for (const pair<pair<int, int>, pair<int, int>> move : allPossibleMoves)
		{
			board temp = *this;
			temp.moveNoCheck(move.first.first, move.first.second, move.second.first, move.second.second);
			attempt = -1 * temp.findWhiteBestScore(depth - 1);
			if (attempt > bestScore)
			{
				bestScore = attempt;
			}
		}
		return bestScore;
	}

	void board::findBlackBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth)
	{
		bestScoreT = -100000;
		int attempt;
		for (begin; begin < end; begin++)
		{
			board temp = *this;
			temp.moveNoCheck(PossibleMoves[begin].first.first, PossibleMoves[begin].first.second, PossibleMoves[begin].second.first, PossibleMoves[begin].second.second);
			if (temp.isWhiteCheckmated())
			{
				BestMoveT = PossibleMoves[begin];
				bestScoreT = 100000;
				return;
			}
			else
			{
				attempt = -1* temp.findWhiteBestScore(depth-1);
				if (attempt > bestScoreT)
				{
					bestScoreT = attempt;
					BestMoveT = PossibleMoves[begin];
				}
			}
		}
		return;
	}
	void board::findWhiteBestMoveCore(pair<pair<int, int>, pair<int, int>>& BestMoveT, int& bestScoreT, vector<pair<pair < int, int>, pair<int, int>>>& PossibleMoves, int begin, int end, int depth)
	{
		bestScoreT = -100000;
		int attempt;
		for (begin; begin < end; begin++)
		{
			board temp = *this;
			temp.moveNoCheck(PossibleMoves[begin].first.first, PossibleMoves[begin].first.second, PossibleMoves[begin].second.first, PossibleMoves[begin].second.second);
			if (temp.isBlackCheckmated())
			{
				BestMoveT = PossibleMoves[begin];
				bestScoreT = 100000;
				return;
			}
			else
			{
				attempt = -1 * temp.findBlackBestScore(depth - 1);
				if (attempt > bestScoreT)
				{
					bestScoreT = attempt;
					BestMoveT = PossibleMoves[begin];
				}
			}
		}
		return;
	}


