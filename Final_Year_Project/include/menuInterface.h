#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class MenuInterface
{
public:
	virtual void clickEvent(int x, int y) = 0;
	virtual void keyEvent(std::string skeyPressed) = 0;
	virtual void gameMain(sf::RenderWindow& window, int mX, int mY) = 0;
};

#endif MENUINTERFACE_H