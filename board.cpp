#include "board.h"
#include <iostream>

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
	}
	char board::getPieceAt(int_fast8_t row, int_fast8_t col)
	{
		return CurBoard[row][col];
	}
	void board::setPieceAt(int_fast8_t row, int_fast8_t col, char newPiece)
	{
		CurBoard[row][col] = newPiece;
		return;
	}
	void board::removePiece(int_fast8_t row, int_fast8_t col)
	{
		CurBoard[row][col] = '*';
		return;
	}
	void board::printBoard()
	{
		cout << "X A B C D E F G H" << endl;
		cout << "8 " << CurBoard[8][A] << " " << CurBoard[8][B] << " " << CurBoard[8][C] << " " << CurBoard[8][D] << " " << CurBoard[8][E] << " " << CurBoard[8][F] << " " << CurBoard[8][G] << " " << CurBoard[8][H] << endl;
		cout << "7 " << CurBoard[7][A] << " " << CurBoard[7][B] << " " << CurBoard[7][C] << " " << CurBoard[7][D] << " " << CurBoard[7][E] << " " << CurBoard[7][F] << " " << CurBoard[7][G] << " " << CurBoard[7][H] << endl;
		cout << "6 " << CurBoard[6][A] << " " << CurBoard[6][B] << " " << CurBoard[6][C] << " " << CurBoard[6][D] << " " << CurBoard[6][E] << " " << CurBoard[6][F] << " " << CurBoard[6][G] << " " << CurBoard[6][H] << endl;
		cout << "5 " << CurBoard[5][A] << " " << CurBoard[5][B] << " " << CurBoard[5][C] << " " << CurBoard[5][D] << " " << CurBoard[5][E] << " " << CurBoard[5][F] << " " << CurBoard[5][G] << " " << CurBoard[5][H] << endl;
		cout << "4 " << CurBoard[4][A] << " " << CurBoard[4][B] << " " << CurBoard[4][C] << " " << CurBoard[4][D] << " " << CurBoard[4][E] << " " << CurBoard[4][F] << " " << CurBoard[4][G] << " " << CurBoard[4][H] << endl;
		cout << "3 " << CurBoard[3][A] << " " << CurBoard[3][B] << " " << CurBoard[3][C] << " " << CurBoard[3][D] << " " << CurBoard[3][E] << " " << CurBoard[3][F] << " " << CurBoard[3][G] << " " << CurBoard[3][H] << endl;
		cout << "2 " << CurBoard[2][A] << " " << CurBoard[2][B] << " " << CurBoard[2][C] << " " << CurBoard[2][D] << " " << CurBoard[2][E] << " " << CurBoard[2][F] << " " << CurBoard[2][G] << " " << CurBoard[2][H] << endl;
		cout << "1 " << CurBoard[1][A] << " " << CurBoard[1][B] << " " << CurBoard[1][C] << " " << CurBoard[1][D] << " " << CurBoard[1][E] << " " << CurBoard[1][F] << " " << CurBoard[1][G] << " " << CurBoard[1][H] << endl;
		cout << "-----------------" << endl;
		cout << "Piece Taken:" << endl;
		for (int_fast8_t i = 0; i < TakenPieceBlack.size(); i++)
		{
			cout << TakenPieceBlack[i] << " ";
		}
		cout << endl;
		for (int_fast8_t i = 0; i < TakenPieceWhite.size(); i++)
		{
			cout << TakenPieceWhite[i] << " ";
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
	int board::getWhiteMaterialAdvantage()
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
	int board::getBlackMaterialAdvantage()
	{
		return 0 - getWhiteMaterialAdvantage();
	}
	bool board::isWhite(int_fast8_t row, int_fast8_t col)
	{
		switch (CurBoard[row][col])
		{
		case WhitePawn:
			return true;
		case WhiteRook:
			return true;
		case WhiteKnight:
			return true;
		case WhiteBishop:
			return true;
		case WhiteQueen:
			return true;
		case WhiteKing:
			return true;
		default: return false;
		}
	}
	bool board::isBlack(int_fast8_t row, int_fast8_t col)
	{
		if (isWhite(row, col) || CurBoard[row][col] == Empty)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool board::isInTheBoard(int_fast8_t row, int_fast8_t col)
	{
		if (row > 0 && row < 9 && col > 0 && col < 9)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	vector<pair<int8_t, int8_t>> board::WhiteControlledSquares()
	{
		vector<pair<int8_t, int8_t>> result;
		for (int_fast8_t row = 1; row < 9; row++)
		{
			for (int_fast8_t col = 1; col < 9; col++)
			{
				if (isWhite(row, col))
				{
					if (CurBoard[row][col] == WhitePawn)
					{
						if (isInTheBoard(row + 1, col + 1))
						{
							result.push_back({ row + 1,col + 1 });
						}
						if (isInTheBoard(row + 1, col - 1))
						{
							result.push_back({ row + 1,col - 1 });
						}
					}
					else
					{ 
					vector<pair<int_fast8_t, int_fast8_t>> PossibleMoves = getPossibleMoves(row, col);
						for (int_fast8_t i = 0; i < PossibleMoves.size(); i++)
						{
							result.push_back(PossibleMoves[i]);
						}
					}
				}
			}
		}
		return result;
	}
	vector<pair<int_fast8_t, int_fast8_t>> board::BlackControlledSquares()
	{
		vector<pair<int_fast8_t, int_fast8_t>> result;
		for (int_fast8_t row = 1; row < 9; row++)
		{
			for (int_fast8_t col = 1; col < 9; col++)
			{
				if (isBlack(row, col))
				{
					if (CurBoard[row][col] == BlackPawn)
					{
						if (isInTheBoard(row - 1, col + 1))
						{
							result.push_back({ row - 1,col + 1 });
						}
						if (isInTheBoard(row - 1, col - 1))
						{
							result.push_back({ row - 1,col - 1 });
						}
					}
					else
					{
						vector<pair<int_fast8_t, int_fast8_t>> PossibleMoves = getPossibleMoves(row, col);
						for (int_fast8_t i = 0; i < PossibleMoves.size(); i++)
						{
							result.push_back(PossibleMoves[i]);
						}
					}
				}
			}
		}
		return result;
	}
	bool board::isWhiteControlled(int_fast8_t row, int_fast8_t col)
	{
		vector<pair<int_fast8_t, int_fast8_t>> WhiteControlled = WhiteControlledSquares();
		for (int_fast8_t i = 0; i < WhiteControlled.size(); i++)
		{
			if (WhiteControlled[i].first == row && WhiteControlled[i].second == col)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isBlackControlled(int_fast8_t row, int_fast8_t col)
	{
		vector<pair<int_fast8_t, int_fast8_t>> BlackControlled = BlackControlledSquares();
		for (int i = 0; i < BlackControlled.size(); i++)
		{
			if (BlackControlled[i].first == row && BlackControlled[i].second == col)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isWhiteChecked()
	{
		vector<pair<int_fast8_t, int_fast8_t>> BlackControlled = BlackControlledSquares();
		for (int_fast8_t i = 0; i < BlackControlled.size(); i++)
		{
			if (CurBoard[BlackControlled[i].first][BlackControlled[i].second] == WhiteKing)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isBlackChecked()
	{
		vector<pair<int_fast8_t, int_fast8_t>> WhiteControlled = WhiteControlledSquares();
		for (int_fast8_t i = 0; i < WhiteControlled.size(); i++)
		{
			if (CurBoard[WhiteControlled[i].first][WhiteControlled[i].second] == BlackKing)
			{
				return true;
			}
		}
		return false;
	}
	bool board::isWhiteCheckmated()
	{
		if (isWhiteChecked())
		{
			vector<pair<int_fast8_t, int_fast8_t>> WhiteControlled = WhiteControlledSquares();
			for (int_fast8_t i = 0; i < WhiteControlled.size(); i++)
			{
				vector<pair<int_fast8_t, int_fast8_t>> PossibleMoves = getPossibleMoves(WhiteControlled[i].first, WhiteControlled[i].second);
				for (int_fast8_t j = 0; j < PossibleMoves.size(); j++)
				{
					board NewBoard = *this;
					NewBoard.move(WhiteControlled[i].first, WhiteControlled[i].second, PossibleMoves[j].first, PossibleMoves[j].second);
					if (!NewBoard.isWhiteChecked())
					{
						return false;
					}
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	bool board::isBlackCheckmated()
	{
		if (isBlackChecked())
		{
			vector<pair<int_fast8_t, int_fast8_t>> BlackControlled = BlackControlledSquares();
			for (int_fast8_t i = 0; i < BlackControlled.size(); i++)
			{
				vector<pair<int_fast8_t, int_fast8_t>> PossibleMoves = getPossibleMoves(BlackControlled[i].first, BlackControlled[i].second);
				for (int_fast8_t j = 0; j < PossibleMoves.size(); j++)
				{
					board NewBoard = *this;
					NewBoard.move(BlackControlled[i].first, BlackControlled[i].second, PossibleMoves[j].first, PossibleMoves[j].second);
					if (!NewBoard.isBlackChecked())
					{
						return false;
					}
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	vector<pair<int_fast8_t, int_fast8_t>> board::getPossibleMoves(int_fast8_t row, int_fast8_t col)
	{
		bool UpRowOpen;
		bool DownRowOpen;
		bool RightColOpen;
		bool LeftColOpen;
		bool UpRightOpen;
		bool UpLeftOpen;
		bool DownRightOpen;
		bool DownLeftOpen;
		int_fast8_t Index;
		vector<pair<int_fast8_t, int_fast8_t>> result;
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
		return result;
	}
	vector<pair<int_fast8_t, int_fast8_t>> board::getPossibleEnPassant(int_fast8_t row, int_fast8_t col)
	{
		vector<pair<int_fast8_t, int_fast8_t>> result;
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
	vector<pair<int_fast8_t, int_fast8_t>> board::getPossibleCastling(int_fast8_t row, int_fast8_t col)
	{
		vector<pair<int_fast8_t, int_fast8_t>> result;
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
	void board::move(int_fast8_t row, int_fast8_t col, int_fast8_t newRow, int_fast8_t newCol)
	{
		vector<pair<int_fast8_t, int_fast8_t>> possibleMoves = getPossibleMoves(row, col);
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
			vector<pair<int_fast8_t, int_fast8_t>> possibleEnPassant = getPossibleEnPassant(row, col);
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
				vector<pair<int_fast8_t, int_fast8_t>> possibleCastling = getPossibleCastling(row, col);
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
					throw "Invalid Move";
				}
			}
		}
	}