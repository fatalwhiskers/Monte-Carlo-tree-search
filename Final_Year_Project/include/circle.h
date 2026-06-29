/** \file circle.h
* Header file for the circle class.
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include <memory>
#include <SFML/Graphics.hpp>

//! The circle Class
/*!
This class builds a standard circle bounding box.
Inherits from Movable and collides with aabb obb and cirle
*/
class circle 

{
private:

	/** a pointer to a sfml texture so the texture only has to loaded once*/
	sf::Texture m_pTexture;
	/** The x coordinate*/
	int iX;
	/** The y coordinate*/
	int iY;
	/** a pointer to a sfml texture so the texture only has to loaded once*/
	sf::Sprite sprite;
public:
	/**
	The only constructor availible, takes all variables.
	\param the x coordinate for display.
	\param the y coordinate for display.
	\param tex is the texture used.
	*/
	circle(int x, int y, sf::Texture tex);

	/**
	The draw function which draws the aabb with the current texture.
	\param window The sfml window you want to display to.
	*/
	void draw(sf::RenderWindow& win);
};

#endif CIRCLE_H