/** \file connect4game.h
* Header file for the connect4game class.
*/

#ifndef CONNECT4GAME_H
#define CONNECT4GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "textureLoader.h"
#include "circle.h"
#include <iostream>
#include "c4state.h"
#include "mtsc.h"
#include "UCT.h"
#include "score.h"
#include "HigestReward.h"
#include "mostVisited.h"
#include "weightedChild.h"
#include "MenuInterface.h"
//! The connect4game Class
/*!
This class runs the connect 4 game and controls the mtsc search player and ai
*/

class connect4game : public MenuInterface
{
public:


	/** The Gamestage enum sets states of the game*/
	enum GameStage { Intro, level, GAME_OVER, Restart};
	/** The Player enum sets state of the players human or artifical inteligence*/
	static enum Player { human, UCTplayer, Greedy, visited, reward, heavy};

	/** construter allows the game to allocate states
	\param rw stands for the render window you want the states to render in.
	\param PlayerOne the state of the player.
	\param PlayerTwo the state of the player.
	\param playerOneIterations the amount of iterations for the player.
	\param playerTwoIterations the amount of iterations for the player.
	*/
	connect4game(sf::RenderWindow& rw, Player PlayerOne, Player PlayerTwo, int playerOneIterations, int playerTwoIterations);

	/** The add circle function creates a circle and places it in the specified coloum
	\param The coloum for placemnt.
	\param The int player determins the colour placed in the coloum.
	*/
	void addcircle(unsigned int column, int player);

	/** A pointer to the render window so the gamestates can access it
	\param m_win the window for loading.
	*/
	sf::RenderWindow* m_win;
	/** The main function for the game loop uses the states
	\param rw the window for loading.
	\param x is the width of the screen.
	\param y is the height of the screen.
	*/
	void gameMain(sf::RenderWindow& rw, int x, int y);
	/** The when the screen is clicked
	\param x position of the click.
	\param y position of the click.
	*/
	void clickEvent(int x, int y);
	/** The when a key is pressed
	\param a string to say which key is pressed
	*/
	void keyEvent(std::string sKeyPressed);

	/** loads the level takes the height and width and places emty circle to create the game board
	\param x is the width of the screen.
	\param y is the height of the screen.
	*/
	void loadLevel(int x, int y);

	/** A vector of circles which will be passed to draw and update*/
	std::vector<std::shared_ptr<circle>> m_GameObs;
	/** a iterator to the m_GameObs*/
	std::vector<std::shared_ptr<circle>>::iterator m_GameObjectit;
	/** A varible for the texture load to load textures*/
	textureLoader tex;
	/** A varible to run the mtsc Tree for the ai */
	mtcs<c4state, int> mtcsTree;
	/** A varible to run the reward Tree for the ai */
	HighestReward<c4state, int> rewardTree;
	/** A varible to run the visited Tree for the ai */
	mostVisited<c4state, int> visitedTree;
	/** A varible to run the weigted Tree for the ai */
	WeightedChild<c4state, int> weigtedTree;
	/** A varible to run the UCT Tree for the ai */
	UCT<c4state, int> UCTTree;
	/** A state varible update and access the static varibles*/
	c4state con4State;
	

private:
	/** The intial draw flag since there are no players.*/
	bool drawFlag;
	/** allows access to the gamestages fro the game loop.*/
	GameStage m_GameState;
	/** The Player one state.*/
	Player player1;
	/** The Player two state.*/
	Player player2;
	/** makes sure the game is drawn before the next move is allwed to take place.*/
	bool drawn = false;
	/** writes gameover on the board.*/
	score gameOver;
	/** writes press space to restarton the board.*/
	score pressSpace;
	/** The amount of player one iterations.*/
	int PlayerOneIterations;
	/** The amount of player two iterations.*/
	int PlayerTwoIterations;
};

#endif CONNECT4GAME_H