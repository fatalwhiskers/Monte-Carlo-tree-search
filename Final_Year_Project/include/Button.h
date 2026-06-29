/** \file button.h
* Header file for the letter class.
*/


#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "textureLoader.h"
#include <functional>
//! The button Class
/*!
This class will create a clickerble button for the gui
*/
class Button 
{
private:
	/**  A pointer to the function which the button will call when clicked*/
	std::function<void()> func;
	/**  The font of the text*/
	sf::Font font;
	/**  The position of the button*/
	sf::Vector2i position;
	/**  The width and height of the button*/
	sf::Vector2i widthHeight;
	/**  the texture seen when the mouse is not on the button*/
	sf::Texture PassiveTexture;
	/**  the texture seen when the mouse is on the button*/
	sf::Texture ActiveTexture;
	/**  the text on the button*/
	std::string ButtonText;
	/**  the text generation*/
	sf::Text text;
public:
	/**  bool which controls when a button is highlighted*/
	bool highlighted;
	/**  bool which controls when a button is selected*/
	bool selected;
	/**  The id of the button*/
	std::string name;

	/** The default constructor.*/
	Button();
	/** The default constructor.
	\param position the position of the button.
	\param cb the callback function.
	\param passiveTextureName the non highlited texture.
	\param activeTextureName the highlighted texture.
	\param text the text on the button.
	\param name the name of the button.
	*/
	Button(sf::Vector2i position, std::function<void()> cb, sf::Texture passiveTextureName, sf::Texture activeTextureName, std::string text, std::string name = "");
	/** The creation of a button.
	\param position the position of the button.
	\param cb the callback function.
	\param passiveTextureName the non highlited texture.
	\param activeTextureName the highlighted texture.
	\param text the text on the button.
	\param name the name of the button.
	*/
	void createButton(sf::Vector2i position, std::function<void()> cb, sf::Texture passiveTextureName, sf::Texture activeTextureName, std::string text);
	~Button();
	/** The text setter.
	\param text the text to set to.
	*/
	void setText(std::string text);
	/** The text getter.*/
	std::string getText();
	/** The call the callback function.*/
	void theCallBack(); // always sad
	/** draws the highlighted button.*/
	void drawActive();
	/** draws the non highlighted button.*/
	void drawPassive();
	/** clears all the varibles of the button.*/
	void clear();
	/** renders the button decided which draw to call.
	\param rw the render window to render to.
	*/
	void render(sf::RenderWindow& rw);
	/** presses the button.*/
	void pressed();
	/** presses the button.
	\param x the x coordinate of the mouse.
	\param y the y coordinate of the mouse.
	*/
	bool withInButtonBounds(int x, int y);

};

#endif BUTTON_H