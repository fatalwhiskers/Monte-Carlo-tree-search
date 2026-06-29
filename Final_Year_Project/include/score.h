/** \file score.h
* Header file for the score class.
*/
#ifndef score_H
#define score_H

#include <SFML\Graphics.hpp>
#include <iostream>

//! The score Class

/*!
This class writes text to the screen and numbers
*/
class score 

{
private:
	
	/** A int type for x position.*/
	int x;
	/** A int type for y position.*/
	int y;
	/** A bool type if you want the int value or just text.*/
	
	/** A string type for the text yopu want to be displayed to the screen.*/
	std::string display;
	/** A sfml font type for the fony you to load and use curently set to arial.*/
	sf::Font font;

	int fontSize;
public:
	/** The standard construter displays the score and text.*/
	score();
	/** The standard construter displays the score and text.
	\param x The new value for the x position.
	\param y The new value for the y position.
	\param display message you want to display to the screen.
	\param textOnly disables the score int value so only text is displayed.
	*/
	void set(int x, int y, std::string display, int size = 50);
	/**
	The draw function which draws the aabb with the current texture.
	\param window The sfml window you want to display to.
	*/
	void draw(sf::RenderWindow& win, sf::Color col = sf::Color(0, 0, 0));
};

#endif score_H