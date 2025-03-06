
#include "board.h"
#include "static.cpp"
#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>

#pragma execution_character_set("utf-8")
    board::board()
    {
        CurBoard = { 
            // X     A     B     C     D     E     F     G     H
            {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},//row 0 
            {Empty,WhiteRook,WhiteKnight,WhiteBishop,WhiteQueen,WhiteKing,WhiteBishop,WhiteKnight,WhiteRook},//row 1
            {Empty,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn},//row 2
            {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},//row 3
            {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},//row 4
            {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},//row 5
            {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty},//row 6
            {Empty,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn},//row 7
            {Empty,BlackRook,BlackKnight,BlackBishop,BlackQueen,BlackKing,BlackBishop,BlackKnight,BlackRook}//row 8
        };
        TakenPieceBlack = {};
        TakenPieceWhite = {};
        WhiteCastleKingSideQualified = true;
        WhiteCastleQueenSideQualified = true;
        BlackCastleKingSideQualified = true;
        BlackCastleQueenSideQualified = true;
		MoveHistory = {};
		mover = White;
		unicodeSupported = false;
    }
	board::board(const board& theboard)
	{
		CurBoard = theboard.CurBoard;
		TakenPieceBlack = theboard.TakenPieceBlack;
		TakenPieceWhite = theboard.TakenPieceWhite;
		WhiteCastleKingSideQualified = theboard.WhiteCastleKingSideQualified;
		WhiteCastleQueenSideQualified = theboard.WhiteCastleQueenSideQualified;
		BlackCastleKingSideQualified = theboard.BlackCastleKingSideQualified;
		BlackCastleQueenSideQualified = theboard.BlackCastleQueenSideQualified;
		MoveHistory = theboard.MoveHistory;
		mover = theboard.mover;
		unicodeSupported = theboard.unicodeSupported;
	}
	void board::setUnicodeSupported(bool support)
	{
		unicodeSupported = support;
	}
	void board::PromptForUnicodeSupport()
	{
		system("chcp 65001");
		cout << "Does your terminal support unicode characters? (Y/N)" << endl;
		cout << "For example, is this white pawn (" << u8"\u2659" << ") correctly displayed ? If not, type N." << endl;
		char unicode;
		cin >> unicode;
		if (unicode == 'Y')
		{
			unicodeSupported = true;
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
		}
		else
		{
			unicodeSupported = false;
			cout << "In this case, the pieces will be displayed as follows:" << endl;
			cout << "White Pawn: P" << endl;
			cout << "White Rook: R" << endl;
			cout << "White Knight: N" << endl;
			cout << "White Bishop: S" << endl;
			cout << "White Queen: Q" << endl;
			cout << "White King: K" << endl;
			cout << "Black Pawn: p" << endl;
			cout << "Black Rook: r" << endl;
			cout << "Black Knight: n" << endl;
			cout << "Black Bishop: s" << endl;
			cout << "Black Queen: q" << endl;
			cout << "Black King: k" << endl;
			cout << "Empty Square: *" << endl;
		}
	}
	char board::getPieceAt(int row, int col)
	{
		return CurBoard[row][col];
	}
	void board::setPieceAt(int row, int col, char newPiece)
	{
		CurBoard[row][col] = newPiece;
		return;
	}
	void board::removePiece(int row, int col)
	{
		CurBoard[row][col] = '*';
		return;
	}
	void board::PieceCast(char piece)
	{
		if (!unicodeSupported)
		{
			cout << piece;
			return;
		}
		switch (piece)
		{
		case WhitePawn:
			cout << u8"\u2659";
			break;
		case WhiteRook:
			cout << u8"\u2656";
			break;
		case WhiteKnight:
			cout << u8"\u2658";
			break;
		case WhiteBishop:
			cout << u8"\u2657";
			break;
		case WhiteQueen:
			cout << u8"\u2655";
			break;
		case WhiteKing:
			cout << u8"\u2654";
			break;
		case BlackPawn:
			cout << u8"\u265F";
			break;
		case BlackRook:
			cout << u8"\u265C";
			break;
		case BlackKnight:
			cout << u8"\u265E";
			break;
		case BlackBishop:
			cout << u8"\u265D";
			break;
		case BlackQueen:
			cout << u8"\u265B";
			break;
		case BlackKing:
			cout << u8"\u265A";
			break;
		case Empty:
			cout << '*';
		}
		return;
	}
	void board::printBoard()
	{
		cout << "X A B C D E F G H" << endl;
		for (int i = 1; i < 9; i++)
		{
			cout << i << " ";
			for (int j = 1; j < 9; j++)
			{
				PieceCast(CurBoard[i][j]);
				cout << " ";
			}
			cout << endl;
		}
		cout << "Piece Taken:" << endl;
		for (int i = 0; i < TakenPieceBlack.size(); i++)
		{
			PieceCast(TakenPieceBlack[i]);
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < TakenPieceWhite.size(); i++)
		{
			PieceCast(TakenPieceWhite[i]);
			cout << " ";
		}
		cout << endl;

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
	int board::getWhiteMaterialAdvantage() const
	{
		int BlackValueOnBoard = 0;
		int WhiteValueOnBoard = 0;
		for (int row = 1; row < 9; row++)
		{
			for (int col = 1; col < 9; col++)
			{
				switch (CurBoard[row][col])
				{
				case WhitePawn:
					WhiteValueOnBoard += 1;
					break;
				case WhiteRook:
					WhiteValueOnBoard += 5;
					break;
				case WhiteKnight:
					WhiteValueOnBoard += 3;
					break;
				case WhiteBishop:
					WhiteValueOnBoard += 3;
					break;
				case WhiteQueen:
					WhiteValueOnBoard += 9;
					break;
				case BlackPawn:
					BlackValueOnBoard += 1;
					break;
				case BlackRook:
					BlackValueOnBoard += 5;
					break;
				case BlackKnight:
					BlackValueOnBoard += 3;
					break;
				case BlackBishop:
					BlackValueOnBoard += 3;
					break;
				case BlackQueen:
					BlackValueOnBoard += 9;
					break;
				}
			}
		}
		return WhiteValueOnBoard - BlackValueOnBoard;
	}
	int board::getBlackMaterialAdvantage() const
	{
		return 0 - getWhiteMaterialAdvantage();
	}
	bool board::isWhite(const int& row, const int& col) const
	{
		const char piece = CurBoard[row][col];
		return (piece == 'r' || piece == 's' || piece == 'n' || piece == 'q' || piece == 'p' || piece == 'k');
	}
	bool board::isBlack(const int& row, const int& col) const
	{
		const char piece = CurBoard[row][col];
		return (piece == 'R' || piece == 'S' || piece == 'N' ||	piece == 'Q' || piece == 'P' || piece == 'K');
	}
	bool board::isInTheBoard(const int& row, const int& col) const
	{
		return (row >= 1 && row <= 8 && col >= 1 && col <= 8);
	}
	 vector<pair<int, int>> board::WhiteOccupiedSquares() const
	{
		vector<pair<int, int>> result;
		result.reserve(16);
		for (int row = 1; row < 9; row++)
		{
			for (int col = 1; col < 9; col++)
			{
				if (isWhite(row, col))
				{
					result.push_back({ row,col });
				}
			}
		}
		return result;
	}
	vector<pair<int, int>> board::BlackOccupiedSquares() const
	{
		vector<pair<int, int>> result;
		result.reserve(16);
		for (int row = 1; row < 9; row++)
		{
			for (int col = 1; col < 9; col++)
			{
				if (isBlack(row, col))
				{
					result.push_back({ row,col });
				}
			}
		}
		return result;
	}
	vector<pair<int, int>> board::WhiteControlledSquares() const
	{
		vector<pair<int, int>> const WhitePieces = WhiteOccupiedSquares();
		vector<pair<int, int>> result;
		bool UpRowOpen;
		bool DownRowOpen;
		bool RightColOpen;
		bool LeftColOpen;
		bool UpRightOpen;
		bool UpLeftOpen;
		bool DownRightOpen;
		bool DownLeftOpen;
		int Index;
		for (int i = 0; i < WhitePieces.size(); i++)
		{
			switch (CurBoard[WhitePieces[i].first][WhitePieces[i].second])
			{
			case WhitePawn:
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second - 1 });
				}
				break;
			case WhiteRook:
				UpRowOpen = true;
				DownRowOpen = true;
				RightColOpen = true;
				LeftColOpen = true;
				Index = WhitePieces[i].first + 1;
				while (UpRowOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[Index][WhitePieces[i].second] == Empty)
						{
							result.push_back({ Index,WhitePieces[i].second });
							Index++;
						}
						else if (isWhite(Index, WhitePieces[i].second))
						{
							UpRowOpen = false;
						}
						else
						{
							result.push_back({ Index,WhitePieces[i].second });
							UpRowOpen = false;
						}
					}
					else
					{
						UpRowOpen = false;
					}
				}
				Index = WhitePieces[i].first - 1;
				while (DownRowOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[Index][WhitePieces[i].second] == Empty)
						{
							result.push_back({ Index,WhitePieces[i].second });
							Index--;
						}
						else if (isWhite(Index, WhitePieces[i].second))
						{
							DownRowOpen = false;
						}
						else
						{
							result.push_back({ Index,WhitePieces[i].second });
							DownRowOpen = false;
						}
					}
					else
					{
						DownRowOpen = false;
					}
				}
				Index = WhitePieces[i].second + 1;
				while (RightColOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[WhitePieces[i].first][Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first,Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first, Index))
						{
							RightColOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first,Index });
							RightColOpen = false;
						}
					}
					else
					{
						RightColOpen = false;
					}
				}
				Index = WhitePieces[i].second - 1;
				while (LeftColOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[WhitePieces[i].first][Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first,Index });
							Index--;
						}
						else if (isWhite(WhitePieces[i].first, Index))
						{
							LeftColOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first,Index });
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
				if (isInTheBoard(WhitePieces[i].first + 2, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first + 2,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first + 2, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first + 2,WhitePieces[i].second - 1 });
				}
				if (isInTheBoard(WhitePieces[i].first - 2, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first - 2,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first - 2, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first - 2,WhitePieces[i].second - 1 });
				}
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second + 2))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second + 2 });
				}
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second - 2))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second - 2 });
				}
				if (isInTheBoard(WhitePieces[i].first - 1, WhitePieces[i].second + 2))
				{
					result.push_back({ WhitePieces[i].first - 1,WhitePieces[i].second + 2 });
				}
				if (isInTheBoard(WhitePieces[i].first - 1, WhitePieces[i].second - 2))
				{
					result.push_back({ WhitePieces[i].first - 1,WhitePieces[i].second - 2 });
				}
				break;
			case WhiteBishop:
				UpRightOpen = true;
				UpLeftOpen = true;
				DownRightOpen = true;
				DownLeftOpen = true;
				Index = 1;
				while (UpRightOpen)
				{
					if (isInTheBoard(WhitePieces[i].first + Index, WhitePieces[i].second + Index))
					{
						if (CurBoard[WhitePieces[i].first + Index][WhitePieces[i].second + Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second + Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first + Index, WhitePieces[i].second + Index))
						{
							UpRightOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second + Index });
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
					if (isInTheBoard(WhitePieces[i].first + Index, WhitePieces[i].second - Index))
					{
						if (CurBoard[WhitePieces[i].first + Index][WhitePieces[i].second - Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second - Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first + Index, WhitePieces[i].second - Index))
						{
							UpLeftOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second - Index });
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
					if (isInTheBoard(WhitePieces[i].first - Index, WhitePieces[i].second + Index))
					{
						if (CurBoard[WhitePieces[i].first - Index][WhitePieces[i].second + Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second + Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first - Index, WhitePieces[i].second + Index))
						{
							DownRightOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second + Index });
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
					if (isInTheBoard(WhitePieces[i].first - Index, WhitePieces[i].second - Index))
					{
						if (CurBoard[WhitePieces[i].first - Index][WhitePieces[i].second - Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second - Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first - Index, WhitePieces[i].second - Index))
						{
							DownLeftOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second - Index });
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
				UpRowOpen = true;
				DownRowOpen = true;
				RightColOpen = true;
				LeftColOpen = true;
				Index = WhitePieces[i].first + 1;
				while (UpRowOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[Index][WhitePieces[i].second] == Empty)
						{
							result.push_back({ Index,WhitePieces[i].second });
							Index++;
						}
						else if (isWhite(Index, WhitePieces[i].second))
						{
							UpRowOpen = false;
						}
						else
						{
							result.push_back({ Index,WhitePieces[i].second });
							UpRowOpen = false;
						}
					}
					else
					{
						UpRowOpen = false;
					}
				}
				Index = WhitePieces[i].first - 1;
				while (DownRowOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[Index][WhitePieces[i].second] == Empty)
						{
							result.push_back({ Index,WhitePieces[i].second });
							Index--;
						}
						else if (isWhite(Index, WhitePieces[i].second))
						{
							DownRowOpen = false;
						}
						else
						{
							result.push_back({ Index,WhitePieces[i].second });
							DownRowOpen = false;
						}
					}
					else
					{
						DownRowOpen = false;
					}
				}
				Index = WhitePieces[i].second + 1;
				while (RightColOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[WhitePieces[i].first][Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first,Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first, Index))
						{
							RightColOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first,Index });
							RightColOpen = false;
						}
					}
					else
					{
						RightColOpen = false;
					}
				}
				Index = WhitePieces[i].second - 1;
				while (LeftColOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[WhitePieces[i].first][Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first,Index });
							Index--;
						}
						else if (isWhite(WhitePieces[i].first, Index))
						{
							LeftColOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first,Index });
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
					if (isInTheBoard(WhitePieces[i].first + Index, WhitePieces[i].second + Index))
					{
						if (CurBoard[WhitePieces[i].first + Index][WhitePieces[i].second + Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second + Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first + Index, WhitePieces[i].second + Index))
						{
							UpRightOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second + Index });
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
					if (isInTheBoard(WhitePieces[i].first + Index, WhitePieces[i].second - Index))
					{
						if (CurBoard[WhitePieces[i].first + Index][WhitePieces[i].second - Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second - Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first + Index, WhitePieces[i].second - Index))
						{
							UpLeftOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first + Index,WhitePieces[i].second - Index });
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
					if (isInTheBoard(WhitePieces[i].first - Index, WhitePieces[i].second + Index))
					{
						if (CurBoard[WhitePieces[i].first - Index][WhitePieces[i].second + Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second + Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first - Index, WhitePieces[i].second + Index))
						{
							DownRightOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second + Index });
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
					if (isInTheBoard(WhitePieces[i].first - Index, WhitePieces[i].second - Index))
					{
						if (CurBoard[WhitePieces[i].first - Index][WhitePieces[i].second - Index] == Empty)
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second - Index });
							Index++;
						}
						else if (isWhite(WhitePieces[i].first - Index, WhitePieces[i].second - Index))
						{
							DownLeftOpen = false;
						}
						else
						{
							result.push_back({ WhitePieces[i].first - Index,WhitePieces[i].second - Index });
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
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second });
				}
				if (isInTheBoard(WhitePieces[i].first - 1, WhitePieces[i].second))
				{
					result.push_back({ WhitePieces[i].first - 1,WhitePieces[i].second });
				}
				if (isInTheBoard(WhitePieces[i].first, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first,WhitePieces[i].second - 1 });
				}
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first + 1, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first + 1,WhitePieces[i].second - 1 });
				}
				if (isInTheBoard(WhitePieces[i].first - 1, WhitePieces[i].second + 1))
				{
					result.push_back({ WhitePieces[i].first - 1,WhitePieces[i].second + 1 });
				}
				if (isInTheBoard(WhitePieces[i].first - 1, WhitePieces[i].second - 1))
				{
					result.push_back({ WhitePieces[i].first - 1,WhitePieces[i].second - 1 });
				}
				break;
			}
		}
		return result;
	}
	vector<pair<int, int>> board::BlackControlledSquares() const
	{
		vector<pair<int, int>> BlackPieces = BlackOccupiedSquares();
		vector<pair<int, int>> result;
		bool UpRowOpen;
		bool DownRowOpen;
		bool RightColOpen;
		bool LeftColOpen;
		bool UpRightOpen;
		bool UpLeftOpen;
		bool DownRightOpen;
		bool DownLeftOpen;
		int Index;
		for (int i = 0; i < BlackPieces.size(); i++)
		{
			switch (CurBoard[BlackPieces[i].first][BlackPieces[i].second])
			{
			case BlackPawn:
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second - 1 });
				}
				break;
			case BlackRook:
				UpRowOpen = true;
				DownRowOpen = true;
				RightColOpen = true;
				LeftColOpen = true;
				Index = BlackPieces[i].first + 1;
				while (UpRowOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[Index][BlackPieces[i].second] == Empty)
						{
							result.push_back({ Index,BlackPieces[i].second });
							Index++;
						}
						else if (isBlack(Index, BlackPieces[i].second))
						{
							UpRowOpen = false;
						}
						else
						{
							result.push_back({ Index,BlackPieces[i].second });
							UpRowOpen = false;
						}
					}
					else
					{
						UpRowOpen = false;
					}
				}
				Index = BlackPieces[i].first - 1;
				while (DownRowOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[Index][BlackPieces[i].second] == Empty)
						{
							result.push_back({ Index,BlackPieces[i].second });
							Index--;
						}
						else if (isBlack(Index, BlackPieces[i].second))
						{
							DownRowOpen = false;
						}
						else
						{
							result.push_back({ Index,BlackPieces[i].second });
							DownRowOpen = false;
						}
					}
					else
					{
						DownRowOpen = false;
					}
				}
				Index = BlackPieces[i].second + 1;
				while (RightColOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[BlackPieces[i].first][Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first,Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first, Index))
						{
							RightColOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first,Index });
							RightColOpen = false;
						}
					}
					else
					{
						RightColOpen = false;
					}
				}
				Index = BlackPieces[i].second - 1;
				while (LeftColOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[BlackPieces[i].first][Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first,Index });
							Index--;
						}
						else if (isBlack(BlackPieces[i].first, Index))
						{
							LeftColOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first,Index });
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
				if (isInTheBoard(BlackPieces[i].first + 2, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first + 2,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first + 2, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first + 2,BlackPieces[i].second - 1 });
				}
				if (isInTheBoard(BlackPieces[i].first - 2, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first - 2,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first - 2, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first - 2,BlackPieces[i].second - 1 });
				}
				if (isInTheBoard(BlackPieces[i].first + 1, BlackPieces[i].second + 2))
				{
					result.push_back({ BlackPieces[i].first + 1,BlackPieces[i].second + 2 });
				}
				if (isInTheBoard(BlackPieces[i].first + 1, BlackPieces[i].second - 2))
				{
					result.push_back({ BlackPieces[i].first + 1,BlackPieces[i].second - 2 });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second + 2))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second + 2 });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second - 2))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second - 2 });
				}
				break;
			case BlackBishop:
				UpRightOpen = true;
				UpLeftOpen = true;
				DownRightOpen = true;
				DownLeftOpen = true;
				Index = 1;
				while (UpRightOpen)
				{
					if (isInTheBoard(BlackPieces[i].first + Index, BlackPieces[i].second + Index))
					{
						if (CurBoard[BlackPieces[i].first + Index][BlackPieces[i].second + Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second + Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first + Index, BlackPieces[i].second + Index))
						{
							UpRightOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second + Index });
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
					if (isInTheBoard(BlackPieces[i].first + Index, BlackPieces[i].second - Index))
					{
						if (CurBoard[BlackPieces[i].first + Index][BlackPieces[i].second - Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second - Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first + Index, BlackPieces[i].second - Index))
						{
							UpLeftOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second - Index });
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
					if (isInTheBoard(BlackPieces[i].first - Index, BlackPieces[i].second + Index))
					{
						if (CurBoard[BlackPieces[i].first - Index][BlackPieces[i].second + Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second + Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first - Index, BlackPieces[i].second + Index))
						{
							DownRightOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second + Index });
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
					if (isInTheBoard(BlackPieces[i].first - Index, BlackPieces[i].second - Index))
					{
						if (CurBoard[BlackPieces[i].first - Index][BlackPieces[i].second - Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second - Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first - Index, BlackPieces[i].second - Index))
						{
							DownLeftOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second - Index });
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
				UpRowOpen = true;
				DownRowOpen = true;
				RightColOpen = true;
				LeftColOpen = true;
				Index = BlackPieces[i].first + 1;
				while (UpRowOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[Index][BlackPieces[i].second] == Empty)
						{
							result.push_back({ Index,BlackPieces[i].second });
							Index++;
						}
						else if (isBlack(Index, BlackPieces[i].second))
						{
							UpRowOpen = false;
						}
						else
						{
							result.push_back({ Index,BlackPieces[i].second });
							UpRowOpen = false;
						}
					}
					else
					{
						UpRowOpen = false;
					}
				}
				Index = BlackPieces[i].first - 1;
				while (DownRowOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[Index][BlackPieces[i].second] == Empty)
						{
							result.push_back({ Index,BlackPieces[i].second });
							Index--;
						}
						else if (isBlack(Index, BlackPieces[i].second))
						{
							DownRowOpen = false;
						}
						else
						{
							result.push_back({ Index,BlackPieces[i].second });
							DownRowOpen = false;
						}
					}
					else
					{
						DownRowOpen = false;
					}
				}
				Index = BlackPieces[i].second + 1;
				while (RightColOpen)
				{
					if (Index < 9)
					{
						if (CurBoard[BlackPieces[i].first][Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first,Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first, Index))
						{
							RightColOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first,Index });
							RightColOpen = false;
						}
					}
					else
					{
						RightColOpen = false;
					}
				}
				Index = BlackPieces[i].second - 1;
				while (LeftColOpen)
				{
					if (Index > 0)
					{
						if (CurBoard[BlackPieces[i].first][Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first,Index });
							Index--;
						}
						else if (isBlack(BlackPieces[i].first, Index))
						{
							LeftColOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first,Index });
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
					if (isInTheBoard(BlackPieces[i].first + Index, BlackPieces[i].second + Index))
					{
						if (CurBoard[BlackPieces[i].first + Index][BlackPieces[i].second + Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second + Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first + Index, BlackPieces[i].second + Index))
						{
							UpRightOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second + Index });
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
					if (isInTheBoard(BlackPieces[i].first + Index, BlackPieces[i].second - Index))
					{
						if (CurBoard[BlackPieces[i].first + Index][BlackPieces[i].second - Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second - Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first + Index, BlackPieces[i].second - Index))
						{
							UpLeftOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first + Index,BlackPieces[i].second - Index });
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
					if (isInTheBoard(BlackPieces[i].first - Index, BlackPieces[i].second + Index))
					{
						if (CurBoard[BlackPieces[i].first - Index][BlackPieces[i].second + Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second + Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first - Index, BlackPieces[i].second + Index))
						{
							DownRightOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second + Index });
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
					if (isInTheBoard(BlackPieces[i].first - Index, BlackPieces[i].second - Index))
					{
						if (CurBoard[BlackPieces[i].first - Index][BlackPieces[i].second - Index] == Empty)
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second - Index });
							Index++;
						}
						else if (isBlack(BlackPieces[i].first - Index, BlackPieces[i].second - Index))
						{
							DownLeftOpen = false;
						}
						else
						{
							result.push_back({ BlackPieces[i].first - Index,BlackPieces[i].second - Index });
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
				if (isInTheBoard(BlackPieces[i].first + 1, BlackPieces[i].second))
				{
					result.push_back({ BlackPieces[i].first + 1,BlackPieces[i].second });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second });
				}
				if (isInTheBoard(BlackPieces[i].first, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first,BlackPieces[i].second - 1 });
				}
				if (isInTheBoard(BlackPieces[i].first + 1, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first + 1,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first + 1, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first + 1,BlackPieces[i].second - 1 });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second + 1))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second + 1 });
				}
				if (isInTheBoard(BlackPieces[i].first - 1, BlackPieces[i].second - 1))
				{
					result.push_back({ BlackPieces[i].first - 1,BlackPieces[i].second - 1 });
				}
				break;
			}
		}
		return result;
	}
	bool board::isWhiteControlled(int row, int col) const
	{
		vector<pair<int, int>> WhiteControlled = WhiteControlledSquares();
		for (int i = 0; i < WhiteControlled.size(); i++)
		{
			if (WhiteControlled[i].first == row && WhiteControlled[i].second == col)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isBlackControlled(int row, int col) const
	{
		vector<pair<int, int>> BlackControlled = BlackControlledSquares();
		for (int i = 0; i < BlackControlled.size(); i++)
		{
			if (BlackControlled[i].first == row && BlackControlled[i].second == col)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isWhiteChecked() const
	{
		vector<pair<int, int>> BlackControlled = BlackControlledSquares();
		for (int i = 0; i < BlackControlled.size(); i++)
		{
			if (CurBoard[BlackControlled[i].first][BlackControlled[i].second] == WhiteKing)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isBlackChecked() const
	{
		vector<pair<int, int>> WhiteControlled = WhiteControlledSquares();
		for (int i = 0; i < WhiteControlled.size(); i++)
		{
			if (CurBoard[WhiteControlled[i].first][WhiteControlled[i].second] == BlackKing)
			{
				return true;
			}
		}
		return false;
	}
	bool board::willWhiteBeChecked(int row, int col, int newRow, int newCol) const
	{ 
		board NewBoard = *this;
		NewBoard.moveNoCheck(row, col, newRow, newCol);
		return NewBoard.isWhiteChecked();
	}
	bool board::willBlackBeChecked(int row, int col, int newRow, int newCol) const
	{
		board NewBoard = *this;
		NewBoard.moveNoCheck(row, col, newRow, newCol);
		return NewBoard.isBlackChecked();
	}
	bool board::isWhiteCheckmated()
	{
		if (!isWhiteChecked())
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
	vector<pair<pair < int, int>, pair<int, int>> > board::getAllWhitePossibleMoves() const
	{
		vector<pair<pair < int, int>, pair<int, int>> > result;
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 9; j++)
			{
				if (isWhite(i, j))
				{
					vector<pair<int, int>> possibleMoves = getPossibleMoves(i, j);
					vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(i, j); 
					vector<pair<int, int>> possibleCastling = getPossibleCastling(i, j);
					for (int k = 0; k < possibleMoves.size(); k++)
					{
						result.push_back({ {i,j},possibleMoves[k] });
					}
					for (int k = 0; k < possibleEnPassant.size(); k++)
					{
						result.push_back({ {i,j},possibleEnPassant[k] });
					}
					for (int k = 0; k < possibleCastling.size(); k++)
					{
						result.push_back({ {i,j},possibleCastling[k] });
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
					vector<pair<int, int>> possibleMoves = getPossibleMoves(i, j);
					vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(i, j);
					vector<pair<int, int>> possibleCastling = getPossibleCastling(i, j);
					for (int k = 0; k < possibleMoves.size(); k++)
					{
						result.push_back({ {i,j},possibleMoves[k] });
					}
					for (int k = 0; k < possibleEnPassant.size(); k++)
					{
						result.push_back({ {i,j},possibleEnPassant[k] });
					}
					for (int k = 0; k < possibleCastling.size(); k++)
					{
						result.push_back({ {i,j},possibleCastling[k] });
					}
				}
			}
		}
		return result;
	}
	bool board::move(int row, int col, int newRow, int newCol)
	{
		vector<pair<int, int>> possibleMoves = getPossibleMoves(row, col);
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
			vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(row, col);
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
				vector<pair<int, int>> possibleCastling = getPossibleCastling(row, col);
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
		vector<pair<int, int>> possibleEnPassant = getPossibleEnPassant(row, col);
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
			vector<pair<int, int>> possibleCastling = getPossibleCastling(row, col);
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
		if (depth == 0)
		{
			if (allPossibleMoves.size() > 32)
			{
				depth = 4;
			}
			else
			{
				depth = 5;
			}
		}
		pair<pair<int, int>, pair<int, int>> BestMoveT1;
		pair<pair<int, int>, pair<int, int>> BestMoveT2;
		pair<pair<int, int>, pair<int, int>> BestMoveT3;
		pair<pair<int, int>, pair<int, int>> BestMoveT4;
		pair<pair<int, int>, pair<int, int>> BestMoveT5;
		pair<pair<int, int>, pair<int, int>> BestMoveT6;
		pair<pair<int, int>, pair<int, int>> BestMoveT7;
		pair<pair<int, int>, pair<int, int>> BestMoveT8;
		int bestScoreT1;
		int bestScoreT2;
		int bestScoreT3;
		int bestScoreT4;
		int bestScoreT5;
		int bestScoreT6;
		int bestScoreT7;
		int bestScoreT8;
		int base = allPossibleMoves.size();
		if (base > 8)
		{
			double factor = static_cast<double>(base) / 8.0;
			std::thread t1(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT1), std::ref(bestScoreT1), std::ref(allPossibleMoves), 0, std::round(factor), depth);
			std::thread t2(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT2), std::ref(bestScoreT2), std::ref(allPossibleMoves), std::round(factor), std::round(2.0 * factor), depth);
			std::thread t3(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT3), std::ref(bestScoreT3), std::ref(allPossibleMoves), std::round(2.0 * factor), std::round(3.0 * factor), depth);
			std::thread t4(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT4), std::ref(bestScoreT4), std::ref(allPossibleMoves), std::round(3.0 * factor), std::round(4.0 * factor), depth);
			std::thread t5(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT5), std::ref(bestScoreT5), std::ref(allPossibleMoves), std::round(4.0 * factor), std::round(5.0 * factor), depth);
			std::thread t6(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT6), std::ref(bestScoreT6), std::ref(allPossibleMoves), std::round(5.0 * factor), std::round(6.0 * factor), depth);
			std::thread t7(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT7), std::ref(bestScoreT7), std::ref(allPossibleMoves), std::round(6.0 * factor), std::round(7.0 * factor), depth);
			std::thread t8(&board::findWhiteBestMoveCore, this, std::ref(BestMoveT8), std::ref(bestScoreT8), std::ref(allPossibleMoves), std::round(7.0 * factor), allPossibleMoves.size(), depth);

			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			t8.join();

			// Determine the best move from the results of all threads
			bestscore = bestScoreT1;
			vector<pair<pair<int, int>, pair<int, int>>> BestMoveList;
			BestMoveList.push_back(BestMoveT1);
			if (bestScoreT2 > bestscore) {
				bestscore = bestScoreT2;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT2);
			}
			else if (bestScoreT2 == bestscore)
			{
				BestMoveList.push_back(BestMoveT2);
			}

			if (bestScoreT3 > bestscore) {
				bestscore = bestScoreT3;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT3);
			}
			else if (bestScoreT3 == bestscore)
			{
				BestMoveList.push_back(BestMoveT3);
			}

			if (bestScoreT4 > bestscore) {
				bestscore = bestScoreT4;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT4);
			}
			else if (bestScoreT4 == bestscore)
			{
				BestMoveList.push_back(BestMoveT4);
			}

			if (bestScoreT5 > bestscore) {
				bestscore = bestScoreT5;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT5);
			}
			else if (bestScoreT5 == bestscore)
			{
				BestMoveList.push_back(BestMoveT5);
			}

			if (bestScoreT6 > bestscore) {
				bestscore = bestScoreT6;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT6);
			}
			else if (bestScoreT6 == bestscore)
			{
				BestMoveList.push_back(BestMoveT6);
			}

			if (bestScoreT7 > bestscore) {
				bestscore = bestScoreT7;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT7);
			}
			else if (bestScoreT7 == bestscore)
			{
				BestMoveList.push_back(BestMoveT7);
			}

			if (bestScoreT8 > bestscore) {
				bestscore = bestScoreT8;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT8);
			}
			else if (bestScoreT4 == bestscore)
			{
				BestMoveList.push_back(BestMoveT8);
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
		else
		{
			findWhiteBestMoveCore(BestMoveT1, bestScoreT1, allPossibleMoves, 0, base, depth);
			return { BestMoveT1,bestScoreT1 };
		}
	}
	pair<pair<pair<int, int>, pair<int, int>>, int> board::findBlackBestMove(int depth)
	{
		pair<pair<int, int>, pair<int, int>> bestMove;
		int bestscore = -100000;
		vector<pair<pair < int, int>, pair<int, int>> > allPossibleMoves = getAllBlackPossibleMoves();
		if (depth == 0)
		{
			if (allPossibleMoves.size() > 32)
			{
				depth = 4;
			}
			else
			{
				depth = 5;
			}
		}
		pair<pair<int, int>, pair<int, int>> BestMoveT1;
		pair<pair<int, int>, pair<int, int>> BestMoveT2;
		pair<pair<int, int>, pair<int, int>> BestMoveT3;
		pair<pair<int, int>, pair<int, int>> BestMoveT4;
		pair<pair<int, int>, pair<int, int>> BestMoveT5;
		pair<pair<int, int>, pair<int, int>> BestMoveT6;
		pair<pair<int, int>, pair<int, int>> BestMoveT7;
		pair<pair<int, int>, pair<int, int>> BestMoveT8;
		int bestScoreT1;
		int bestScoreT2;
		int bestScoreT3;
		int bestScoreT4;
		int bestScoreT5;
		int bestScoreT6;
		int bestScoreT7;
		int bestScoreT8;
		int base = allPossibleMoves.size();
		if (base > 8)
		{
			double factor = static_cast<double>(base) / 8.0;
			std::thread t1(&board::findBlackBestMoveCore, this, std::ref(BestMoveT1), std::ref(bestScoreT1), std::ref(allPossibleMoves), 0, std::round(factor), depth);
			std::thread t2(&board::findBlackBestMoveCore, this, std::ref(BestMoveT2), std::ref(bestScoreT2), std::ref(allPossibleMoves), std::round(factor), std::round(2.0 * factor), depth);
			std::thread t3(&board::findBlackBestMoveCore, this, std::ref(BestMoveT3), std::ref(bestScoreT3), std::ref(allPossibleMoves), std::round(2.0 * factor), std::round(3.0 * factor), depth);
			std::thread t4(&board::findBlackBestMoveCore, this, std::ref(BestMoveT4), std::ref(bestScoreT4), std::ref(allPossibleMoves), std::round(3.0 * factor), std::round(4.0 * factor), depth);
			std::thread t5(&board::findBlackBestMoveCore, this, std::ref(BestMoveT5), std::ref(bestScoreT5), std::ref(allPossibleMoves), std::round(4.0 * factor), std::round(5.0 * factor), depth);
			std::thread t6(&board::findBlackBestMoveCore, this, std::ref(BestMoveT6), std::ref(bestScoreT6), std::ref(allPossibleMoves), std::round(5.0 * factor), std::round(6.0 * factor), depth);
			std::thread t7(&board::findBlackBestMoveCore, this, std::ref(BestMoveT7), std::ref(bestScoreT7), std::ref(allPossibleMoves), std::round(6.0 * factor), std::round(7.0 * factor), depth);
			std::thread t8(&board::findBlackBestMoveCore, this, std::ref(BestMoveT8), std::ref(bestScoreT8), std::ref(allPossibleMoves), std::round(7.0 * factor), allPossibleMoves.size(), depth);

			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
			t6.join();
			t7.join();
			t8.join();

			// Determine the best move from the results of all threads
			bestscore = bestScoreT1;
			vector<pair<pair<int, int>, pair<int, int>>> BestMoveList;
			BestMoveList.push_back(BestMoveT1);
			if (bestScoreT2 > bestscore) {
				bestscore = bestScoreT2;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT2);
			}
			else if (bestScoreT2 == bestscore)
			{
				BestMoveList.push_back(BestMoveT2);
			}

			if (bestScoreT3 > bestscore) {
				bestscore = bestScoreT3;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT3);
			}
			else if (bestScoreT3 == bestscore)
			{
				BestMoveList.push_back(BestMoveT3);
			}

			if (bestScoreT4 > bestscore) {
				bestscore = bestScoreT4;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT4);
			}
			else if (bestScoreT4 == bestscore)
			{
				BestMoveList.push_back(BestMoveT4);
			}

			if (bestScoreT5 > bestscore) {
				bestscore = bestScoreT5;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT5);
			}
			else if (bestScoreT5 == bestscore)
			{
				BestMoveList.push_back(BestMoveT5);
			}

			if (bestScoreT6 > bestscore) {
				bestscore = bestScoreT6;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT6);
			}
			else if (bestScoreT6 == bestscore)
			{
				BestMoveList.push_back(BestMoveT6);
			}

			if (bestScoreT7 > bestscore) {
				bestscore = bestScoreT7;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT7);
			}
			else if (bestScoreT7 == bestscore)
			{
				BestMoveList.push_back(BestMoveT7);
			}

			if (bestScoreT8 > bestscore) {
				bestscore = bestScoreT8;
				BestMoveList.clear();
				BestMoveList.push_back(BestMoveT8);
			}
			else if (bestScoreT4 == bestscore)
			{
				BestMoveList.push_back(BestMoveT8);
			}
			int Complexity=0;
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
		else
		{
			findBlackBestMoveCore(BestMoveT1, bestScoreT1, allPossibleMoves, 0, base, depth);
			return { BestMoveT1,bestScoreT1 };
		}
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


