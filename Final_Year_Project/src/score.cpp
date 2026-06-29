#include "score.h"

score::score()
{
	font.loadFromFile("images/arial.ttf");
}

void score::set(int h, int g, std::string text1, int size)
{
	x = h;
	y = g;
	display = text1;
	//font.loadFromFile("images/arial.ttf");
	fontSize = size;
}


void score::draw(sf::RenderWindow& win, sf::Color col)
{
		std::string concaternate = display;
		sf::Text text(concaternate, font, fontSize);
		text.setColor(col);
		text.setPosition(sf::Vector2f((float)x, (float)y));
		win.draw(text);
}