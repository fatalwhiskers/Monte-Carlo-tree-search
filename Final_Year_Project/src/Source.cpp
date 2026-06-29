#include "node.h"
#include "mtsc.h"
#include "c4state.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "connect4game.h"
#include "checkerGame.h"
#include "circle.h"
#include "MenuInterface.h"
#include "Menu.h"
#include <memory>
/*
int main()
{
	mtcs<state> tree;
	node<state>* ptr; 
	
	system("pause");
	return 0;
}*/

int main()
{
	int screenwidth = 800;
	int screenheight = 700;

	sf::RenderWindow window(sf::VideoMode(screenwidth, screenheight), "My window");
	//std::unique_ptr<MenuInterface> game(new Menu(window));
	//MenuInterface * game;
	//game = new checkerGame(window);
	Menu Game(window);
	
	sf::View currentView = window.getView();
	while (window.isOpen())
	{
		sf::Event event;
		std::string sKeyPressed;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == event.MouseButtonReleased )
			{
				Game.clickEvent(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
			else if ((event.type == sf::Event::KeyPressed))
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space: sKeyPressed = "SPACE"; break;
				}
				Game.keyEvent(sKeyPressed);
			}

			else if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 58 && event.text.unicode >47)
				{
					if (Menu::userInput == "0")
					{
						Menu::userInput.erase(Menu::userInput.getSize() - 1);
						Menu::userInput.insert(Menu::userInput.getSize(), event.text.unicode);
					}
					else
					{
						Menu::userInput.insert(Menu::userInput.getSize(), event.text.unicode);
					}
				}
				
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace) // delete the last character
				{
					if (Menu::userInput.getSize() > 0)
					{
						Menu::userInput.erase(Menu::userInput.getSize() - 1);
					}
					if (Menu::userInput.getSize() == 0)
					{
						Menu::userInput = "0";
					}
				}
				else if(event.key.code == sf::Keyboard::Return) // complete
				{
					Menu::BackToMenu = true;
				}
			}
				
		}

		window.clear(sf::Color::Blue);

		Game.gameMain(window, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		window.display();



	}
	return 0;
}