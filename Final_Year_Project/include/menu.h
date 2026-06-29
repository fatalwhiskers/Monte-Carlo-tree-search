/** \file menu.h
* Header file for the menu class.
*/

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "textureLoader.h"
#include "circle.h"
#include <iostream>
#include "c4state.h"
#include "mtsc.h"
#include "score.h"
#include "MenuInterface.h"
#include "Button.h"
#include "checkerGame.h"
#include "connect4game.h"
#include "menuInterface.h"
//#define MAX_NUMBER_OF_ITEMS 2

//! The menu Class
/*!
This is the class which controls the menus and game game code
*/

class Menu : public MenuInterface
{
public:
	/** construter allows the menu to allocate states
	\param rw stands for the render window you want the states to render in.
	*/
	Menu(sf::RenderWindow& rw);
	~Menu();
	/** A bool hich when true will return the user back to the menu*/
	static bool BackToMenu;
	/** The texture loader to load textures*/
	textureLoader tex;
	/** The when the screen is clicked
	\param x position of the click.
	\param y position of the click.
	*/
	void clickEvent(int x, int y);
	/** The inputed numbers from the keyboard controlled by SFML*/
	static sf::String userInput;
	/** The when a key is pressed
	\param a string to say which key is pressed
	*/
	void keyEvent(std::string skeyPressed);
	/** The main function for the game loop uses the states
	\param rw the window for loading.
	\param x is the width of the screen.
	\param y is the height of the screen.
	*/
	void gameMain(sf::RenderWindow& window, int mX, int mY);
	/**connect four game selected*/
	void connect();
	/**checkers game selected*/
	void Checkers();
	/** allows user input int the text box*/
	void textBoxPLayerOne();
	/** allows user input int the text box*/
	void textBoxPLayerTwo();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneUCT();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneHuman();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneGreedy();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneHeavy();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneVisited();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerOneReward();

	/** a callback function for a button sets the player two algorithm*/
	void PlayerTwoUCT();
	/** a callback function for a button sets the player two algorithm*/
	void PlayerTwoGreedy();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerTwoHeavy();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerTwoVisited();
	/** a callback function for a button sets the player one algorithm*/
	void PlayerTwoReward();

	/** creates the game ready to be started
	\param window stands for the render window you want the states to render in.
	*/
	void createGame(sf::RenderWindow& window);
	/** starts the game if ready*/
	void Done();
	/** the draw function
	\param rw stands for the render window you want the states to render in.
	*/
	void draw(sf::RenderWindow &window);


private:
	enum GameStage { menu, start, gameStart, NewGame, wait};//!< the possible menu states
	GameStage m_GameState;//!< the state the menu is in
	sf::Font font;//!< the text font
	std::vector<Button> but;//!< A vector of clickable buttons
	std::vector<Button> PlayerOne;//!< A vector of Player One clickable buttons
	std::vector<Button> PlayerTwo;//!< A vector of Player Two clickable buttons
	//Button but[MAX_NUMBER_OF_ITEMS];
	sf::Text text; //!< the text 
	sf::Text player1;//!< the text player1
	sf::Text player2;//!< the text player2
	sf::Text iterations;//!< the text iterations

	std::vector<Button> textBox;//!< A vector of text box buttons
	MenuInterface * game;//!< pointer to the game
	std::string GameToBePlayed;//!< the selected game
	std::string PlayerOneAlgorithm;//!< the selected algorithm
	std::string PlayerTwoAlgorithm;//!< the selected algorithm

	bool click;//!< bool which triggers when clicked
	sf::Vector2i clickPos; //!< the click position

};
#endif MENU_H