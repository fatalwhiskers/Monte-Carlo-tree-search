#include "Button.h"


Button::Button()
{
	
	clear();
}

Button::Button(sf::Vector2i pos, std::function<void()> cb, sf::Texture passiveTextureName, sf::Texture activeTextureName, std::string text,std::string na)
{
	name = na;
	ButtonText = text;
	position = pos;
	func = cb;
	PassiveTexture = passiveTextureName;
	ActiveTexture = activeTextureName;
	widthHeight.x = PassiveTexture.getSize().x;
	widthHeight.y = PassiveTexture.getSize().y;
	highlighted = false;

}
void Button::createButton(sf::Vector2i pos, std::function<void()> cb, sf::Texture passiveTextureName, sf::Texture activeTextureName, std::string text)
{
	name = text;
	ButtonText = text;
	position = pos;
	func = cb;
	PassiveTexture = passiveTextureName;
	ActiveTexture = activeTextureName;
	widthHeight.x = PassiveTexture.getSize().x;
	widthHeight.y = PassiveTexture.getSize().y;
	highlighted = false;

}
void Button::setText(std::string text)
{
	ButtonText = text;
}

std::string Button::getText()
{
	return ButtonText;
}

Button::~Button()
{

}
void Button::clear()
{
	name = "";
	ButtonText = "";
	position = sf::Vector2i(0,0);
	widthHeight = sf::Vector2i(0, 0);
	highlighted = false;
	selected = false;
}

void Button::theCallBack()
{
	func();
}

void Button::render(sf::RenderWindow& rw)
{

	sf::Sprite sprite;
	if (highlighted == true || selected == true)
	{
		sprite.setTexture(ActiveTexture);
		sprite.setPosition(position.x, position.y);
		rw.draw(sprite);
	}
	else
	{
		sprite.setTexture(PassiveTexture);
		sprite.setPosition(position.x, position.y);
		rw.draw(sprite);
	}
	if (!font.loadFromFile("images/arial.ttf"))
	{
		// handle error
	}
	sf::Text text;
	text.setFont(font);
	text.setString(ButtonText);
	text.setColor(sf::Color::Blue);
	text.setCharacterSize(20);
	text.setPosition(position.x + 5, position.y);

	rw.draw(text);
}

bool Button::withInButtonBounds(int x, int y)
{
	if (highlighted == true)
	{
		if (x > position.x && x < position.x + widthHeight.x
			&& y > position.y && y < position.y + widthHeight.y)
		{
			return true;
		}
	}
	else
	{
		if (x > position.x && x < position.x + widthHeight.x
			&& y > position.y && y < position.y + widthHeight.y)
		{
			return true;
		}
	}
	return false;
}