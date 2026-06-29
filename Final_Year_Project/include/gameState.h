/** \file gameState.h
* Header file for the gameState class.
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <memory>
#include <math.h>
#include <iostream>
#include <array>
//! The gameState class

/*!
This class contains the virtual elements for all game states to inherit from.
*/
template <typename tState, typename Move>
class gameState

{
private:
	
public:
	/**  A typedef int of the potental moves of the state this may be changed for differant games*/
	//typedef int Move;

	/** Returns a vector of possible moves to transition the state.*/
	virtual std::vector<Move> getMoves(int player) = 0;
	/** Returns the winning player or 0 if there is none.*/
	virtual int getWinner() = 0;
	/**
	updates the gameboard with the said move and the calls next player.
	\param A interger to place a counter into the coloum .
	*/
	virtual void doMove(Move mov) = 0;
	/** calls get winner and sets the value for the static winning value if a winner is found or there is no possible moves it is set to true.*/
	virtual bool terminal() = 0;
	/** if the board is in an unwinable state or unplayable.*/
	virtual bool hasNoMoves() = 0;
	/** sets the int player to the next player if player one sets to player two and vice versa.*/
	virtual void nextPlayer() = 0;

	/** Returns the winning value for the Ai used to update the stats in the node.*/
	virtual double outcome() = 0;
	/** Returns the current static board.*/
	virtual tState getBoard() = 0;
	/** Returns the player of this state.*/
	virtual int getPlayer() = 0;
	/** 
	sets the player to the int given.
	\param An interger to set the player too .
	*/
	virtual void setPlayer(int play) = 0;
	/** Returns the value of the state at the set point.
	\param An interger to access the state coloum .
	\param An interger to access the state row .
	*/
	virtual int stateAccess(int x, int y) = 0;
	/** fills the board with random moves while it isn't terminal.*/
	virtual void simulate() = 0;
	/** clears the current static board to 0 for replaying the game*/
	virtual void clearCurrentBoard() = 0;
		

};

#endif GAMESTATE_H