/** \file checkers.h
* Header file for the checkers class.
*/

#ifndef CHECKERGAME_H
#define CHECKERGAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "textureLoader.h"
#include "circle.h"
#include <iostream>
#include "checkerState.h"
#include "mtsc.h"
#include "UCT.h"
#include "HigestReward.h"
#include "mostVisited.h"
#include "weightedChild.h"
#include "score.h"
#include "MenuInterface.h"
#include "connect4game.h"
//! The checkers Class
/*!
This class runs the checkers game and controls the mtsc search player and ai
*/

class checkerGame : public MenuInterface
{
public:


	/** The Gamestage enum sets states of the game*/
	enum GameStage { Intro, level, GAME_OVER, Restart , Wait};
	/** construter allows the game to allocate states
	\param rw stands for the render window you want the states to render in.
	\param PlayerOne the state of the player.
	\param PlayerTwo the state of the player.
	\param playerOneIterations the amount of iterations for the player.
	\param playerTwoIterations the amount of iterations for the player.
	*/
	checkerGame(sf::RenderWindow& rw, connect4game::Player PlayerOne, connect4game::Player PlayerTwo, int playerOneIterations, int playerTwoIterations);

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
	/** checks if the humans player move is valid
	\param moves the vector of integers to check.
	*/
	int CheckValidMove(const std::vector<int> &moves);

	/** A vector of circles which will be passed to draw and update*/
	std::vector<std::shared_ptr<circle>> m_GameObs;
	/** a iterator to the m_GameObs*/
	std::vector<std::shared_ptr<circle>>::iterator m_GameObjectit;
	/** A varible for the texture load to load textures*/
	textureLoader tex;
	/** A varible to run the mtsc for the ai */
	mtcs<checkerState, std::vector<int>> mtcsTree;
	/** A varible to run the UCT Tree for the ai */
	UCT<checkerState, std::vector<int>> UCTTree;
	/** A varible to run the reward Tree for the ai */
	HighestReward<checkerState, std::vector<int>> rewardTree;
	/** A varible to run the visited Tree for the ai */
	mostVisited<checkerState, std::vector<int>> visitedTree;
	/** A varible to run the weigted Tree for the ai */
	WeightedChild<checkerState, std::vector<int>> weigtedTree;
	/** A state varible update and access the static varibles*/
	checkerState con4State;


private:
	typedef std::vector<int> Move;
	/** The amount of Player One Wins.*/
	int PlayerOneWins;
	/** The amount of Player Two Wins.*/
	int PlayerTwoWins;
	/** The amount of draws.*/
	int draws;

	/** The intial draw flag since there are no players.*/
	bool drawFlag;
	/** determins if a value is highlighted*/
	bool highlight;
	/** the x coordinate of the highlight*/
	int highlightX;
	/** the y coordinate of the highlight*/
	int highlightY;
	/** allows access to the gamestages fro the game loop.*/
	GameStage m_GameState;
	/** makes sure the game is drawn before the next move is allwed to take place.*/
	bool drawn = false;
	/** writes gameover on the board.*/
	score gameOver;
	/** displays the amount of player one wins.*/
	score player1Score;
	/** displays the amount of player two wins.*/
	score Player2Score;
	/** displays the amount of draws.*/
	score draw;
	/** writes press space to restarton the board.*/
	score pressSpace;
	/** The Player one state.*/
	connect4game::Player player1;
	/** The Player two state.*/
	connect4game::Player player2;
	/** The amount of player one iterations.*/
	int PlayerOneIterations;
	/** The amount of player two iterations.*/
	int PlayerTwoIterations;
};

#endif CHECKERGAME_H