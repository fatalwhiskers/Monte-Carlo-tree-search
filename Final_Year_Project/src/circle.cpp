#include "circle.h"

circle::circle(int x,int y, sf::Texture tex)
{
	iX = x;
	iY = y;
	m_pTexture = tex;
}

void circle::draw(sf::RenderWindow& win)
{

	sprite.setTexture(m_pTexture);
	sprite.setOrigin(sf::Vector2f((float)(0 + m_pTexture.getSize().x / 2), (float)(0 + m_pTexture.getSize().y / 2)));
	sprite.setPosition(sf::Vector2f((float)(iX), (float)(iY)));
	win.draw(sprite);
}