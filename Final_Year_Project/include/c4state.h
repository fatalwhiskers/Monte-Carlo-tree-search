/** \file state.h
* Header file for the state class.
*/

#ifndef C4STATE_H
#define C4STATE_H


#include <memory>
#include <math.h>
#include <iostream>
#include <vector>
#include "gameState.h"
#include <array>
#include <stdlib.h>



//! The state Class
/*!
This class is the game state which is used in the node and mtsc class
inherits from the base game
all states need to inherit from game 
*/

class c4state : public gameState<c4state, int>

{
private:
	int col = 7;//!< An integer for the amount of coloums
	int rows = 6;//!< An integer for the amount of rows
	static int finalplayer;//!< A static value to show the current Player on the playable board used in conect 4 state
	static double winnigValue;//!< The value from the last terminal state
	static c4state currentBoard;//!< This is the playable game board updated from the conect 4 state
	int board[7][6];//!< The board of this node state used in mtsc state 
	int player;//!< The player of this state used in the mtsc and node
	
public:
	/** The default availible constructor 0s out the array.*/
	c4state();
	/**  A typedef int of the potental moves of the state this may be changed for differant games*/
	typedef int Move;

	/** Returns a vector of possible moves to transition the state.*/
	std::vector<Move> getMoves(int player);
	/** Returns the winning player or 0 if there is none.*/
	int getWinner();	
	/**
	updates the gameboard with the said move and the calls next player.
	\param A interger to place a counter into the coloum .
	*/
	void doMove(Move mov);
	/**
	sets the final move once mtsc has decided the best child.
	\param A interger to place a counter into the coloum .
	*/
	void setFinalMove(Move mov); // commits the move to the board
	/** calls get winner and sets the value for the static winning value if a winner is found or there is no possible moves it is set to true.*/
	bool terminal();
	/** if the board is in an unwinable state or unplayable.*/
	bool hasNoMoves();
	/** sets the int player to the next player if player one sets to player two and vice versa.*/
	void nextPlayer();
	/** Sets the player for the board for the starting state.*/
	void setStartingPlayer(int play);

	/** sets the static int finalplayer to the next player if player one sets to player two and vice versa.*/
	void nextfinalplayer();
	/** returns the finalplayer value.*/
	int getfinalplayer();

	/** Returns the winning value for the Ai used to update the stats in the node.*/
	double outcome();
	/** Returns the current static board.*/
	c4state getBoard();
	/** Returns the player of this state.*/
	int getPlayer();
	/** 
	sets the player to the int given.
	\param An interger to set the player too .
	*/
	void setPlayer(int play);
	/** Returns the amount of rows of this state.*/
	int getRows();
	/** Returns the amount of coloums of this state.*/
	int getCols();
	/** Returns the value of the state at the set point.
	\param An interger to access the state coloum .
	\param An interger to access the state row .
	*/
	int stateAccess(int x, int y);
	/** fills the board with random moves while it isn't terminal.*/
	void simulate();
	/** clears the current static board to 0 for replaying the game*/
	void clearCurrentBoard();
};

#endif C4STATE_H