#include "checkerState.h"
#include <time.h>

typedef std::vector<int> Move;

int checkerState::finalplayer;
int checkerState::numberOfTurns;
double checkerState::winnigValue;
checkerState checkerState::currentBoard;

checkerState::checkerState()
{
	memset(board, 0, sizeof board);
	SetUpBoard();
}

void checkerState::SetUpBoard()
{
	memset(board, 0, sizeof board);
	player1NoMoves = false;
	player2NoMoves = false;
	
	turns = 0;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 1)
			{
				if (i % 2 == 0)
				{
 					board[i][j] = 1;
				}
			}
			else if (j < 3)
			{
				if (i % 2)
				{
					board[i][j] = 1;
				}
			}
			else if (j == 6)
			{
				if (i % 2 == 1)
				{
					board[i][j] = 2;
				}
			}
			else if (j > 4)
			{
				if (i % 2 == 0)
				{
					board[i][j] = 2;
				}
			}
		}
	}

	//board[4][3] = 1;
	//board[5][4] = 4;
	//board[6][5] = 4;
	//board[5][2] = 1;

	/*board[1][4] = 1; // for black box testing
	board[1][2] = 1;
	board[3][6] = 1;
	board[3][2] = 1;
	board[5][4] = 1;
	board[5][6] = 1;
	board[2][1] = 4;
	board[3][4] = 1;*/

}

void checkerState::SetUpCurrentBoard()
{
	memset(currentBoard.board, 0, sizeof currentBoard.board);
	player1NoMoves = false;
	player2NoMoves = false;
	numberOfTurns = 0;
	turns = 0;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j == 1)
			{
				if (i % 2 == 0)
				{
					currentBoard.board[i][j] = 1;
				}
			}
			else if (j < 3)
			{
				if (i % 2)
				{
					currentBoard.board[i][j] = 1;
				}
			}
			else if (j == 6)
			{
				if (i % 2 == 1)
				{
					currentBoard.board[i][j] = 2;
				}
			}
			else if (j>4)
			{
				if (i % 2 == 0)
				{
					currentBoard.board[i][j] = 2;
				}
			}
		}
	}

}

std::vector<Move> checkerState::getMoves(int player)
{
	player2NoMoves = false;
	player1NoMoves = false;

	std::vector<Move> moves;
	int howManyMoves = 0;
	if (getWinner() != 0)
	{
		return moves;
	}
	//#TODO checkJUMPS First Must Always Jump.
	if (player == 1)
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j] == 1)
				{
					Move newMove;
					if ((board[i + 1][j + 1] == 2 || board[i + 1][j + 1] == 4) && i < 6 && j < 6)// not being hit when it should
					{
						if (board[i + 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j + 2);
							bool movesDone = false;
							while (!movesDone && newMove.size() > 0)
							{
								if ((board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 2 || board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 4)
									&& (newMove.at(newMove.size() - 2) + 1 < 7) && (newMove.at(newMove.size() - 1) + 1 < 7)
									&& board[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) + 2] == 0)
								{
										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2) + 2);
										newMove.push_back(newMove.at(newMove.size() - 2) + 2);
								}
								else if ((board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 2 || board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 4)
									&& (newMove.at(newMove.size() - 2) - 1) > 0 && (newMove.at(newMove.size() - 1) + 1 < 7)
									&& board[newMove.at(newMove.size() - 2) - 2][newMove.at(newMove.size() - 1) + 2] == 0)
								{

										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2) - 2);
										newMove.push_back(newMove.at(newMove.size() - 2) + 2);
								}
								else
								{
									movesDone = true;
								}
							}
							if (newMove.size() > 0)
							{
								moves.push_back(newMove);
								newMove.clear();
								howManyMoves++;
							}
						}
					}
					if ((board[i - 1][j + 1] == 2 || board[i - 1][j + 1] == 4) && i > 1 && j < 6)
					{
						if (board[i - 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j + 2);
						}
						bool movesDone = false;
						while (!movesDone && newMove.size() > 0)
						{
							if ((board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 2 || board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 4)
								&& (newMove.at(newMove.size() - 2) -1) > 0 && (newMove.at(newMove.size() - 1) + 1 < 7)
								&& board[newMove.at(newMove.size() - 2) - 2][newMove.at(newMove.size() - 1) + 2] == 0)
							{
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2) - 2);
									newMove.push_back(newMove.at(newMove.size() - 2) + 2);
							}
							else if ((board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 2 || board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 2)
								&& (newMove.at(newMove.size() - 2) + 1 < 7) && (newMove.at(newMove.size() - 1) + 1 < 7)
								&& board[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) + 2] == 0)
							{
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2) + 2);
									newMove.push_back(newMove.at(newMove.size() - 2) + 2);
							}
							else
							{
								movesDone = true;
							}
						}
						if (newMove.size() > 0)
						{
							moves.push_back(newMove);
							newMove.clear();
							howManyMoves++;
						}
							
					}
				}
				else if (board[i][j] == 3)
				{
					Move newMove;
					if ((board[i + 1][j + 1] == 2 || board[i + 1][j + 1] == 4) && i < 6 && j < 6)
					{
						if (board[i + 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j + 2);
							std::vector<Move> temp = getKingMovesPlayer1(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					else if ((board[i - 1][j + 1] == 2 || board[i - 1][j + 1] == 4) && i > 1 && j < 6)
					{
						if (board[i - 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j + 2);
							std::vector<Move> temp = getKingMovesPlayer1(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}

					}
					else if ((board[i - 1][j - 1] == 2 || board[i - 1][j - 1] == 4) && i > 1 && j > 1)
					{
						if (board[i - 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j - 2);
							std::vector<Move> temp = getKingMovesPlayer1(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					else if ((board[i + 1][j - 1] == 2 || board[i + 1][j - 1] == 4) && i < 6 && j > 1)
					{
						if (board[i + 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j - 2);
							std::vector<Move> temp = getKingMovesPlayer1(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					if (newMove.size() > 0)
					{
						moves.push_back(newMove);
						newMove.clear();
						howManyMoves++;
					}
				}
			}
		}
	}

	else if (player == 2)
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j] == 2)
				{
					Move newMove;
					if ((board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == 3) && i > 1 && j > 1)
					{
						if (board[i - 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j - 2);
							bool movesDone = false;
							while (!movesDone && newMove.size() > 0)
							{
								int temp = newMove.size();
								if ((board[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 3)
									&& (newMove.at(temp - 2) - 1) > 0 && (newMove.at(temp - 1) - 1) > 0
									&& board[newMove.at(temp - 2) - 2][newMove.at(temp - 1) - 2] == 0)
								{
										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2) - 2);
										newMove.push_back(newMove.at(newMove.size() - 2) - 2);

								}
								else if ((board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 3)
									&& (newMove.at(temp - 2) + 1 < 7) && (newMove.at(temp - 1) - 1 > 0)
									&& board[newMove.at(temp - 2) + 2][newMove.at(temp - 1) - 2] == 0)
								{

										newMove.push_back(newMove.at(newMove.size() - 2));
										newMove.push_back(newMove.at(newMove.size() - 2));// just added one so still - 2
										newMove.push_back(newMove.at(newMove.size() - 2) + 2);
										newMove.push_back(newMove.at(newMove.size() - 2) - 2);	
								}
								else
								{
									movesDone = true;
								}
							}
							if (newMove.size() > 0)
							{
								moves.push_back(newMove);
								newMove.clear();
								howManyMoves++;
							}
						}
					}
					if ((board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == 3) && i < 6 && j > 1)
					{
						if (board[i + 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j - 2);
						}
						bool movesDone = false;
						while (!movesDone && newMove.size() > 0)
						{
							int temp = newMove.size();
							if ((board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 3)
								&& (newMove.at(temp - 2) + 1 < 7) && (newMove.at(temp - 1) - 1 > 0)
								&& board[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) - 2] == 0)
							{
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2));// just added one so still - 2
									newMove.push_back(newMove.at(newMove.size() - 2) + 2);
									newMove.push_back(newMove.at(newMove.size() - 2) - 2);
							}
							else if ((board[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 3)
								&& (newMove.at(temp - 2) - 1) > 0 && (newMove.at(temp - 1) - 1) > 0
								&& board[newMove.at(temp - 2) - 2][newMove.at(temp - 1) - 2] == 0)
							{
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2));
									newMove.push_back(newMove.at(newMove.size() - 2) - 2);
									newMove.push_back(newMove.at(newMove.size() - 2) - 2);
							}
							else
							{
								movesDone = true;
							}
						}
						if (newMove.size() > 0)
						{
							moves.push_back(newMove);
							newMove.clear();
							howManyMoves++;
						}
						
					}
				}
				else if (board[i][j] == 4)
				{
					Move newMove;
					if ((board[i + 1][j + 1] == 1 || board[i + 1][j + 1] == 3) && i < 6 && j < 6)
					{
						if (board[i + 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j + 2);
							std::vector<Move> temp = getKingMovesPlayer2(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					else if ((board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == 3) && i > 1 && j < 6)
					{
						if (board[i - 2][j + 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j + 2);
							std::vector<Move> temp = getKingMovesPlayer2(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}

					}
					else if ((board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == 3) && i > 1 && j > 1)
					{
						if (board[i - 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i - 2);
							newMove.push_back(j - 2);
							std::vector<Move> temp = getKingMovesPlayer2(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					else if ((board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == 3) && i < 6 && j > 1)
					{
						if (board[i + 2][j - 2] == 0)
						{
							newMove.push_back(i);
							newMove.push_back(j);
							newMove.push_back(i + 2);
							newMove.push_back(j - 2);
							std::vector<Move> temp = getKingMovesPlayer2(newMove);
							moves.insert(moves.end(), temp.begin(), temp.end());
						}
					}
					if (newMove.size() > 0)
					{
						moves.push_back(newMove);
						howManyMoves++;
					}
				}
			}
		}
	}


	if (moves.size() > 0)
	{
		return moves;
	}

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (board[i][j] == 2 && player ==2)
			{
				if (board[i-1][j-1] == 0 && i != 0 && j != 0)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i - 1);
					newMove.push_back(j - 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
				if (board[i + 1][j - 1] == 0 && i != 7 && j != 0)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i + 1);
					newMove.push_back(j - 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
			}
			else if (board[i][j] == 1 && player == 1)
			{
				if (board[i + 1][j + 1] == 0 && i != 7 && j != 7)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i + 1);
					newMove.push_back(j + 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
				if (board[i - 1][j + 1] == 0 && i != 0 && j != 7)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i - 1);
					newMove.push_back(j + 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
			}
			else if (board[i][j] == player + 2)
			{
				if (board[i + 1][j + 1] == 0 && i != 7 && j != 7)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i + 1);
					newMove.push_back(j + 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
				if (board[i + 1][j - 1] == 0 && i != 7 && j != 0)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i + 1);
					newMove.push_back(j - 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
				if (board[i - 1][j + 1] == 0 && i != 0 && j != 7)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i - 1);
					newMove.push_back(j + 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
				if (board[i - 1][j - 1] == 0 && i != 0 && j != 0)
				{
					Move newMove;
					newMove.push_back(i);
					newMove.push_back(j);
					newMove.push_back(i - 1);
					newMove.push_back(j - 1);
					moves.push_back(newMove);
					howManyMoves++;
				}
			}
		}
	}
	
	if (player == 1 && howManyMoves == 0)
	{
		player1NoMoves = true;
	}
	else if (player == 2 && howManyMoves == 0)
	{
		player2NoMoves = true;
	}

	return moves;
}

std::vector<Move> checkerState::getKingMovesPlayer1(Move &newMove, int tempBoard[8][8], bool copyBoard)// pass by referance stupid stupid saves so much cpu power
{
	std::vector<Move> finalMoves;
	bool movesDone = false;
	bool multiJumpDone = false;
	bool jump1 = false;
	bool jump2 = false;
	bool jump3 = false;
	bool jump4 = false;
	int intboard[8][8];
	if (!copyBoard)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				intboard[i][j] = board[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				intboard[i][j] = tempBoard[i][j];
			}
		}
	}
	
	int temp = newMove.size();
	int temp1 = newMove.at(temp - 4) + (((newMove.at(temp - 2) - newMove.at(temp - 4)) / 2));
	int temp2 = newMove.at(temp - 3) + (((newMove.at(temp - 1) - newMove.at(temp - 3)) / 2));
	intboard[newMove.at(temp - 4)][newMove.at(temp - 3)] = 0;
	intboard[temp1][temp2] = 0;
	intboard[newMove.at(temp - 2)][newMove.at(temp - 1)] = 3;
	Move multiJumpMove;
	int jumps = 0; // stops infinite loop
	while (!movesDone && newMove.size() > 0)
	{
		temp = newMove.size();
		if ((intboard[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 2 || intboard[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 4)
			&& (newMove.at(newMove.size() - 2) + 1 < 7) && (newMove.at(newMove.size() - 1) + 1 < 7)
			&& intboard[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) + 2] == 0)
		{
				jump1 = true;
				jumps++;
		}
		if ((intboard[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 2 || intboard[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 4)
			&& (newMove.at(newMove.size() - 2) - 1) > 0 && (newMove.at(newMove.size() - 1) + 1 < 7)
			&& intboard[newMove.at(newMove.size() - 2) - 2][newMove.at(newMove.size() - 1) + 2] == 0)
		{
				jump2 = true;
				jumps++;

		}

		if ((intboard[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 2 || intboard[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 4)
			&& (newMove.at(temp - 2) + 1 < 7) && (newMove.at(temp - 1) - 1 > 0)
			&& intboard[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) - 2] == 0 )
		{
				jump3 = true;
				jumps++;

		}
		if ((intboard[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 2 || intboard[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 4)
			&& (newMove.at(temp - 2) - 1) > 0 && (newMove.at(temp - 1) - 1) > 0
			&& intboard[newMove.at(temp - 2) - 2][newMove.at(temp - 1) - 2] == 0)
		{
				jump4 = true;
				jumps++;
		}
		if (jumps > 1)
		{
			multiJumpMove = newMove;
		}
		if (jump1)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				std::vector<Move> temp = getKingMovesPlayer1(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump1 = false;
		}
		if (jump2)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				std::vector<Move> temp = getKingMovesPlayer1(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump2 = false;
		}
		if (jump3)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));// just added one so still - 2
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));// just added one so still - 2
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				std::vector<Move> temp = getKingMovesPlayer1(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump3 = false;
		}
		if (jump4)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				std::vector<Move> temp = getKingMovesPlayer1(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump4 = false;
		}
		else
		{
			movesDone = true;
			break;
		}
		int temp1 = newMove.at(temp - 4) + (((newMove.at(temp - 2) - newMove.at(temp - 4)) / 2));
		int temp2 = newMove.at(temp - 3) + (((newMove.at(temp - 1) - newMove.at(temp - 3)) / 2));
		intboard[newMove.at(temp - 4)][newMove.at(temp - 3)] = 0;
		intboard[temp1][temp2] = 0;
		intboard[newMove.at(temp - 2)][newMove.at(temp - 1)] = 3;

		multiJumpDone = false;
		jumps = 0;
	}
	finalMoves.push_back(newMove);
	return finalMoves;
}

std::vector<Move> checkerState::getKingMovesPlayer2(Move &newMove, int tempBoard[8][8], bool copyBoard)
{
	std::vector<Move> finalMoves;
	bool movesDone = false;
	bool multiJumpDone = false;
	bool jump1 = false;
	bool jump2 = false;
	bool jump3 = false;
	bool jump4 = false;
	int intboard[8][8];
	if (!copyBoard)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				intboard[i][j] = board[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				intboard[i][j] = tempBoard[i][j];
			}
		}
	}

	int temp = newMove.size();
	int temp1 = newMove.at(temp - 4) + (((newMove.at(temp - 2) - newMove.at(temp - 4)) / 2));
	int temp2 = newMove.at(temp - 3) + (((newMove.at(temp - 1) - newMove.at(temp - 3)) / 2));
	intboard[newMove.at(temp - 4)][newMove.at(temp - 3)] = 0;
	intboard[temp1][temp2] = 0;
	intboard[newMove.at(temp - 2)][newMove.at(temp - 1)] = 4;
	Move multiJumpMove;
	int jumps = 0; // stops infinite loop
	while (!movesDone && newMove.size() > 0)
	{
		temp = newMove.size();
		if ((intboard[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 1 || intboard[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 3)
			&& (newMove.at(newMove.size() - 2) + 1 < 7) && (newMove.at(newMove.size() - 1) + 1 < 7)
			&& intboard[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) + 2] == 0)
		{
			jump1 = true;
			jumps++;
		}
		if ((intboard[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 1 || intboard[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 3)
			&& (newMove.at(newMove.size() - 2) - 1) > 0 && (newMove.at(newMove.size() - 1) + 1 < 7)
			&& intboard[newMove.at(newMove.size() - 2) - 2][newMove.at(newMove.size() - 1) + 2] == 0)
		{
			jump2 = true;
			jumps++;

		}

		if ((intboard[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 1 || intboard[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 3)
			&& (newMove.at(temp - 2) + 1 < 7) && (newMove.at(temp - 1) - 1 > 0)
			&& intboard[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) - 2] == 0)
		{
			jump3 = true;
			jumps++;

		}
		if ((intboard[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 1 || intboard[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 3)
			&& (newMove.at(temp - 2) - 1) > 0 && (newMove.at(temp - 1) - 1) > 0
			&& intboard[newMove.at(temp - 2) - 2][newMove.at(temp - 1) - 2] == 0)
		{
			jump4 = true;
			jumps++;
		}
		if (jumps > 1)
		{
			multiJumpMove = newMove;
		}
		if (jump1)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				std::vector<Move> temp = getKingMovesPlayer2(multiJumpMove, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump1 = false;
		}
		if (jump2)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				std::vector<Move> temp = getKingMovesPlayer2(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump2 = false;
		}
		if (jump3)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));// just added one so still - 2
				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));// just added one so still - 2
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) + 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				std::vector<Move> temp = getKingMovesPlayer2(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump3 = false;
		}
		if (jump4)
		{
			if (jumps == 1 || multiJumpDone == false)
			{
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2));
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
				multiJumpDone = true;
			}
			else
			{
				Move multiJumpTemp = multiJumpMove;
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2));
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				multiJumpTemp.push_back(multiJumpTemp.at(multiJumpTemp.size() - 2) - 2);
				std::vector<Move> temp = getKingMovesPlayer2(multiJumpTemp, intboard, true);
				finalMoves.insert(finalMoves.end(), temp.begin(), temp.end());
			}
			jump4 = false;
		}
		else
		{
			movesDone = true;
			break;
		}
		int temp1 = newMove.at(temp - 4) + (((newMove.at(temp - 2) - newMove.at(temp - 4)) / 2));
		int temp2 = newMove.at(temp - 3) + (((newMove.at(temp - 1) - newMove.at(temp - 3)) / 2));
		intboard[newMove.at(temp - 4)][newMove.at(temp - 3)] = 0;
		intboard[temp1][temp2] = 0;
		intboard[newMove.at(temp - 2)][newMove.at(temp - 1)] = 4;

		multiJumpDone = false;
		jumps = 0;
	}
	finalMoves.push_back(newMove);
	return finalMoves;
}
//
//std::vector<Move> checkerState::getKingMovesPlayer2(Move &newMove, bool jumpV1, bool jumpV2, bool jumpV3, bool jumpV4)// pass by referance genius saves so much cpu power
//{	
//	bool movesDone = false;
//	bool jump1 = jumpV1;
//	bool jump2 = jumpV2;
//	bool jump3 = jumpV3;
//	bool jump4 = jumpV4;
//	int jumps = 0; // stops infinite loop
//	while (!movesDone && newMove.size() > 0)
//	{
//		int temp = newMove.size();
//		if (jumps > 4)
//		{
//			for (int i = 0; i < temp / 2; i ++)
//			{
//				for (int j = 0; j < temp / 2; j++)
//				{
//					if (newMove.at(i) == newMove.at(j + 2) && newMove.at(i + 1) == newMove.at(j + 3))
//					{
//					/*	jumps++;
//						newMove.pop_back();
//						newMove.pop_back();
//						newMove.pop_back();
//						newMove.pop_back();
//						newMove.at(newMove.size() - 16);
//						newMove.at(newMove.size() - 15);*/
//					}
//				}
//			}
//		}
//		if ((board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 1 || board[newMove.at(newMove.size() - 2) + 1][newMove.at(newMove.size() - 1) + 1] == 3)
//			&& (newMove.at(newMove.size() - 2) + 1 < 7) && (newMove.at(newMove.size() - 1) + 1 < 7)
//			&& board[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) + 2] == 0 && jump4)
//		{
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
//				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
//				jump1 = false;
//				jump2 = true;
//				jump3 = true;
//				jump4 = true;
//				jumps++;
//		}
//		else if ((board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 1 || board[newMove.at(newMove.size() - 2) - 1][newMove.at(newMove.size() - 1) + 1] == 3)
//			&& (newMove.at(newMove.size() - 2) - 1) > 0 && (newMove.at(newMove.size() - 1) + 1 < 7)
//			&& board[newMove.at(newMove.size() - 2) - 2][newMove.at(newMove.size() - 1) + 2] == 0 && jump3)
//		{
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
//				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
//				jump1 = true;
//				jump2 = false;
//				jump3 = true;
//				jump4 = true;
//				jumps++;
//		}
//				
//		else if ((board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) + 1][newMove.at(temp - 1) - 1] == 3)
//			&& (newMove.at(temp - 2) + 1 < 7) && (newMove.at(temp - 1) - 1 > 0)
//			&& board[newMove.at(newMove.size() - 2) + 2][newMove.at(newMove.size() - 1) - 2] == 0 && jump2)
//		{
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2));// just added one so still - 2
//				newMove.push_back(newMove.at(newMove.size() - 2) + 2);
//				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
//				jump1 = true;
//				jump2 = true;
//				jump3 = false;
//				jump4 = true;
//				jumps++;
//		}
//		else if ((board[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 1 || board[newMove.at(temp - 2) - 1][newMove.at(temp - 1) - 1] == 3)
//			&& (newMove.at(temp - 2) - 1) > 0 && (newMove.at(temp - 1) - 1) > 0
//			&& board[newMove.at(temp - 2) - 2][newMove.at(temp - 1) - 2] == 0 && jump1)
//		{
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2));
//				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
//				newMove.push_back(newMove.at(newMove.size() - 2) - 2);
//				jump1 = true;
//				jump2 = true;
//				jump3 = true;
//				jump4 = false;
//				jumps++;
//		}
//		else
//		{
//			movesDone = true;
//		}
//	}
//	std::vector<Move> temp;
//	temp.push_back(newMove);
//	return temp;
//}

int checkerState::getWinner()
{
	bool player1HasCounters = false;
	bool player2HasCounters = false;

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (board[i][j] == 1 || board[i][j] == 3)
			{
				player1HasCounters = true;
			}
			if (board[i][j] == 2 || board[i][j] == 4)
			{
				player2HasCounters = true;
			}
			if (player1HasCounters && player2HasCounters)
			{
				break;
			}
		}
	}
	if (player1HasCounters == true && player2HasCounters == false)
	{
		return 1;
	}
	else if (player1HasCounters == false && player2HasCounters == true)
	{
		return 2;
	}
	if (player1NoMoves == true)
	{
		return 2;
	}
	else if (player2NoMoves == true)
	{
		return 1;
	}

	return 0;

}

void checkerState::doMove(Move mov)
{
	bool Jumper = false;
	int currentValue = board[mov.at(0)][mov.at(1)];
	if (mov.size() > 4)
	{
		Jumper = true;
	}
	
	if (!Jumper)
	{
		board[mov.at(0)][mov.at(1)] = 0;
		if (mov.at(3) == 7 && currentValue == 1)
		{
			board[mov.at(2)][mov.at(3)] = 3;
		}
		else if (mov.at(3) == 0 && currentValue == 2)
		{
			board[mov.at(2)][mov.at(3)] = 4;
		}
		else
		{
			board[mov.at(2)][mov.at(3)] = currentValue;
		}
	}
	else
	{
		board[mov.at(0)][mov.at(1)] = 0;
		for (int i = 0; i < (mov.size() / 4); i += 4)
		{
			int temp1 = mov.at(i) + (((mov.at(i + 2) - mov.at(i)) / 2));
			int temp2 = mov.at(i + 1) + (((mov.at(i + 3) - mov.at(i + 1)) / 2));
			board[temp1][temp2] = 0;
		}

		if (mov.at((mov.size() - 2)) == 7 && currentValue == 1)
		{
			board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = 3;
		}
		else if (mov.at((mov.size() - 2)) == 0 && currentValue == 2)
		{
			board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = 4;
		}
		else
		{
			board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = currentValue;
		}
	}

	turns++;
	nextPlayer();
}

void checkerState::setFinalMove(Move mov)
{

	bool Jumper = false;
	int currentValue = currentBoard.board[mov.at(0)][mov.at(1)];

	if (abs(mov.at(3) - mov.at(1)) > 1)
	{
		Jumper = true;
	}
	
	if (!Jumper)
	{
		currentBoard.board[mov.at(0)][mov.at(1)] = 0;
		if (mov.at(3) == 7 && currentValue == 1)
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = 3;
		}
		else if (mov.at(3) == 0 && currentValue == 2)
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = 4;
		}
		else
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = currentValue;
		}
			
	}
	else
	{
		currentBoard.board[mov.at(0)][mov.at(1)] = 0;
		int i = 0;
		for (int j = 0; j < (mov.size() / 4); j ++)
		{
			int temp1 = mov.at(i) + (((mov.at(i + 2) - mov.at(i)) / 2));
			int temp2 = mov.at(i+1) + (((mov.at(i + 3) - mov.at(i + 1)) / 2));
			currentBoard.board[temp1][temp2] = 0;
			i += 4;
		}

		if (mov.at((mov.size() - 1)) == 7 && currentValue == 1)
		{
			currentBoard.board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = 3;
		}
		else if (mov.at((mov.size() - 1)) == 0 && currentValue == 2)
		{
			currentBoard.board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = 4;
		}
		else
		{
			currentBoard.board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = currentValue;
		}
	}
	nextfinalplayer();
	numberOfTurns += 1;
}

void checkerState::setFinalMoveStep(Move mov)
{
	bool Jumper = false;
	int currentValue = currentBoard.board[mov.at(0)][mov.at(1)];

	if (abs(mov.at(3) - mov.at(1)) > 1)
	{
		Jumper = true;
	}

	if (!Jumper)
	{
		currentBoard.board[mov.at(0)][mov.at(1)] = 0;
		if (mov.at(3) == 7 && currentValue == 1)
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = 3;
		}
		else if (mov.at(3) == 0 && currentValue == 2)
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = 4;
		}
		else
		{
			currentBoard.board[mov.at(2)][mov.at(3)] = currentValue;
		}

	}
	else
	{
		currentBoard.board[mov.at(0)][mov.at(1)] = 0;
		int i = 0;
		for (int j = 0; j < (mov.size() / 4); j++)
		{
			int temp1 = mov.at(i) + (((mov.at(i + 2) - mov.at(i)) / 2));
			int temp2 = mov.at(i + 1) + (((mov.at(i + 3) - mov.at(i + 1)) / 2));
			currentBoard.board[temp1][temp2] = 0;
			i += 4;
		}

		currentBoard.board[mov.at(mov.size() - 2)][mov.at(mov.size() - 1)] = currentValue;
	}
}

bool checkerState::terminal()
{
	//win and loss conditions and height conditions

	int temp = getWinner();

	int player1Checkers = 0;
	int player2Checkers = 0;
	double total;

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 1)
			{
				player1Checkers++;
			}
			else if (board[i][j] == 3)
			{
				player1Checkers += 2;
			}
			if (board[i][j] == 2)
			{
				player2Checkers++;
			}
			else if (board[i][j] == 4)
			{
				player2Checkers += 2;
			}
		}
	}

	if (currentBoard.finalplayer == 1)
	{
		total = player1Checkers - player2Checkers;
	}
	else
	{
		total = player2Checkers - player1Checkers;
	}

	if (temp != 0)
	{
		if (temp == 1)
		{
			winnigValue = 0 + (total * 0.1);
			return true;
		}
		else
		{
			winnigValue = 1 + (total * 0.1);
			return true;
		}
	}
	else if (turns > 150 || numberOfTurns > 150)
	{		
		winnigValue = 0.1 + (total * 0.1);
		return true;
	}

return false;

}

bool checkerState::gameTerminal(int Player1Moves, int Player2Moves)
{
	//win and loss conditions and height conditions
	int temp = 0;

	bool player1HasCounters = false;
	bool player2HasCounters = false;

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (board[i][j] == 1 || board[i][j] == 3)
			{
				player1HasCounters = true;
			}
			if (board[i][j] == 2 || board[i][j] == 4)
			{
				player2HasCounters = true;
			}
			if (player1HasCounters && player2HasCounters)
			{
				break;
			}
		}
	}
	if (player1HasCounters == true && player2HasCounters == false)
	{
		temp = 1;
	}
	else if (player1HasCounters == false && player2HasCounters == true)
	{
		temp = 2;
	}
	if (Player1Moves == 0)
	{
		temp = 2;
	}
	else if (Player2Moves == 0)
	{
		temp = 1;
	}	

	if (temp != 0)
	{
		if (temp == 1)
		{
			winnigValue = 0;
			return true;
		}
		else
		{
			winnigValue = 1;
			return true;
		}
	}
	else if (numberOfTurns > 150)
	{
		winnigValue = 0.1;
		return true;
	}

	return false;

}

bool checkerState::hasNoMoves()
{
	if (player1NoMoves)
	{
		return true;
	}
	if (player2NoMoves)
	{
		return true;
	}
	return false;
}

void checkerState::nextPlayer()
{
	if (player == 1)
	{
		player = 2;
	}
	else
	{
		player = 1;
	}
}

void checkerState::nextfinalplayer()
{
	if (finalplayer == 1)
	{
		finalplayer = 2;
	}
	else
	{
		finalplayer = 1;
	}
}

int checkerState::getfinalplayer()
{

	return finalplayer;
}

double checkerState::outcome()
{
	return winnigValue;
}

checkerState checkerState::getBoard()
{
	return currentBoard;
}

int checkerState::getPlayer()
{
	return player;
}

void checkerState::setStartingPlayer(int play)
{
	currentBoard.player = play;
}

void checkerState::setPlayer(int play)
{
	finalplayer = play;
	player = 2;
}

int checkerState::getRows()
{
	return rows;
}

int checkerState::getCols()
{
	return col;
}

int checkerState::stateAccess(int x, int y)
{
	return this->board[x][y];
}

int checkerState::currentStateAccess(int x, int y)
{
	return this->currentBoard.board[x][y];
}

void checkerState::simulate()
{
	std::srand(time(NULL));
	int random;
	checkerState* st = this;
	int i = 0;
	std::vector<Move> movs = getMoves(player);

	while (!st->terminal())
	{
		if (movs.size() == 0)
		{
			break;
		}
		random = std::rand() % (movs.size());
		st->doMove(movs.at(random));
		movs = getMoves(player);
	}


}

void checkerState::clearCurrentBoard()
{

	memset(currentBoard.board, 0, sizeof currentBoard.board);
}