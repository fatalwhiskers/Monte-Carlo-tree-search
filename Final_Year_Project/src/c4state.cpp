#include "c4state.h"
#include <time.h>

typedef int Move;

int c4state::finalplayer;
double c4state::winnigValue;
c4state c4state::currentBoard;

c4state::c4state()
{
	 // last col is for the players turn this leaves som memory over head #TODO test new ways
	memset(board, 0, sizeof board);

}

std::vector<Move> c4state::getMoves(int player)
{
	std::vector<Move> moves;
	
	if (getWinner() != 0)
	{
		return moves;
	}

	for (int i = 0; i < col; i++)
	{
		if (board[i][5] == 0)
			{
				moves.push_back(i);
			}
	}
	return moves;
}

int c4state::getWinner() // to sort out win conditions shouldnt be possible to win 19960 out of 19962 games using randoms
{
	for (int i = 0; i < col; i++)
	{
		if (i < (col - 3))
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j] == 0)
				{
					break;
				}
				else
				{
					int temp = board[i][j];

					if (j < 3)
					{
						if (board[i][j + 1] == temp)
						{
							if (board[i][j + 2] == temp)
							{
								if (board[i][j + 3] == temp)
								{
									return temp;
								}
							}
						}

						if (board[i + 1][j + 1] == temp)
						{
							if (board[i + 2][j + 2] == temp)
							{
								if (board[i + 3][j + 3] == temp)
								{
									return temp;
								}
							}
						}

						if (board[i + 1][j] == temp)
						{
							if (board[i + 2][j] == temp)
							{
								if (board[i + 3][j] == temp)
								{
									return temp;
								}
							}
						}

					}

					else
					{
						if (board[i + 1][j] == temp)
						{
							if (board[i + 2][j] == temp)
							{
								if (board[i + 3][j] == temp)
								{
									return temp;
								}
							}
						}
						if (board[i + 1][j - 1] == temp)
						{
							if (board[i + 2][j - 2] == temp)
							{
								if (board[i + 3][j - 3] == temp)
								{
									return temp;
								}
							}
						}

					}

				}
			}
		}
		else
		{
			for (int j = 0; j < rows - 3; j++)
			{
				if (board[i][j] == 0)
				{
					break;
				}
				else
				{
					int temp = board[i][j];

					if (board[i][j + 1] == temp)
					{
						if (board[i][j + 2] == temp)
						{
							if (board[i][j + 3] == temp)
							{
								return temp;
							}
						}
					}

				}
			}
		}

	}
	return 0;

}

void c4state::doMove(Move mov)
{
	
		for (int i = 0; i < rows; i++)
		{
			if (board[mov][i] == 0)
			{
				board[mov][i] = player;
				break;
			}
		}
		nextPlayer();
}

void c4state::setFinalMove(Move mov)
{

	for (int i = 0; i < rows; i++)
	{
		if (currentBoard.board[mov][i] == 0)
		{
			currentBoard.board[mov][i] = finalplayer;
			break;
		}
	}
	nextfinalplayer();
}

bool c4state::terminal()
{
	//win and loss conditions and height conditions
	
	int temp = getWinner();

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
	if (hasNoMoves() == true)
	{
		winnigValue = 0.5;
		return true;
	}

	return false;


}

bool c4state::hasNoMoves()
{
	for (int i = 0; i < col; i++)
	{
		if (board[i][5] == 0)
		{
			return false;
		}
	}

	return true;
	
}

void c4state::nextPlayer()
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
void c4state::setStartingPlayer(int play)
{
	currentBoard.player = play;
}

void c4state::nextfinalplayer()
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

int c4state::getfinalplayer()
{
	
	return finalplayer;
}

double c4state::outcome()
{
	return winnigValue;
}

c4state c4state::getBoard()
{
	return currentBoard;
}

int c4state::getPlayer()
{
	return player;
}

void c4state::setPlayer(int play)
{
	finalplayer = play;
	player = 2;
}

int c4state::getRows()
{
	return rows;
}

int c4state::getCols()
{
	return col;
}

int c4state::stateAccess(int x, int y)
{
	return this->board[x][y];
}

void c4state::simulate()
{
	std::srand(time(NULL));
	int random;
	c4state* st = this;
	while (!st->terminal())
	{
		random = std::rand() % (col);
		
		if (board[random][5] == 0)
		{
			st->doMove(random);
		}
	}


}

void c4state::clearCurrentBoard()
{

	memset(currentBoard.board, 0, sizeof currentBoard.board);
}