#include "Menu.h"

 sf::String Menu::userInput;
 bool Menu::BackToMenu;

Menu::Menu(sf::RenderWindow& rw)
{
	if (!font.loadFromFile("images/arial.ttf"))
	{
		// handle error
	}

	if (!tex.loadTexture("c4Button", "images/connectButton.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("c4Buttoninv", "images/connectButtonInv.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("Button", "images/Button.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("Buttoninv", "images/ButtonInv.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("CheckerButton", "images/CheckersButton.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("CheckerButtoninv", "images/CheckersButtonInv.png"))
	{
		std::cout << "error file player 1 not loaded";
	}
	if (!tex.loadTexture("background", "images/cool.png"))
	{
		std::cout << "error file background 1 not loaded";
	}
	if (!tex.loadTexture("TextBox", "images/TextBox.png"))
	{
		std::cout << "error file background 1 not loaded";
	}
	if (!tex.loadTexture("TextBoxinv", "images/TextBoxInv.png"))
	{
		std::cout << "error file background 1 not loaded";
	}

	if (!tex.loadTexture("Done", "images/DoneButton.png"))
	{
		std::cout << "error file background 1 not loaded";
	}
	if (!tex.loadTexture("DoneInv", "images/DoneButtonInv.png"))
	{
		std::cout << "error file background 1 not loaded";
	}
	BackToMenu = false;
	m_GameState = menu;
	//but[0].createButton(sf::Vector2i(25, 50), "player1", "player1", "");
	
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setString("Click a game to play");
	text.setPosition(sf::Vector2f(275, 25));

	player1.setFont(font);
	player1.setColor(sf::Color::White);
	player1.setString("");
	player1.setPosition(sf::Vector2f(50, 25));

	player2.setFont(font);
	player2.setColor(sf::Color::White);
	player2.setString("");
	player2.setPosition(sf::Vector2f(575, 25));

	iterations.setFont(font);
	iterations.setColor(sf::Color::White);
	iterations.setCharacterSize(20);
	iterations.setString("");
	iterations.setPosition(sf::Vector2f(575, 25));

	//menu[0].setFont(font);
	//menu[0].setColor(sf::Color::Red);
	//menu[0].setString("Player One settings");
	//menu[0].setPosition(sf::Vector2f(25, 50));

	//menu[1].setFont(font);
	//menu[1].setColor(sf::Color::White);
	//menu[1].setString("Player Two settings");
	//menu[1].setPosition(sf::Vector2f(rw.getSize().x - 300,  50));

	//menu[2].setFont(font);
	//menu[2].setColor(sf::Color::White);
	//menu[2].setString("Exit");
	//menu[2].setPosition(sf::Vector2f((rw.getSize().x / 2) - 25, rw.getSize().y -100));
}


Menu::~Menu()
{
}

void Menu::clickEvent(int x, int y)
{
	switch (m_GameState)
	{
	case Menu::NewGame:
		game->clickEvent(x,y);
		break;

	default:
		for (int i = 0; i < but.size(); i++)
		{
			if (but[i].withInButtonBounds(x, y) == true)
			{
				but[i].theCallBack();
			}
		}
		for (int i = 0; i < PlayerOne.size(); i++)
		{
			if (PlayerOne[i].withInButtonBounds(x, y) == true)
			{
				PlayerOne[i].theCallBack();
			}
		}
		for (int i = 0; i < PlayerTwo.size(); i++)
		{
			if (PlayerTwo[i].withInButtonBounds(x, y) == true)
			{
				PlayerTwo[i].theCallBack();
			}
		}
		for (int i = 0; i < textBox.size(); i++)
		{
			textBox[i].highlighted = false;
			if (textBox[i].withInButtonBounds(x, y) == true)
			{
				textBox[i].theCallBack();
			}
		}
	break;
	}
}

void Menu::keyEvent(std::string skeyPressed)
{
	switch (m_GameState)
	{
	case Menu::NewGame:
		game->keyEvent(skeyPressed);
		break;

	default:
		break;
	}
}

void Menu::connect()
{
	GameToBePlayed = "connect";
	m_GameState = start;
}

void Menu::Checkers()
{
	GameToBePlayed = "checkers";
	m_GameState = start;
}

void Menu::textBoxPLayerOne()
{
	for (int i = 0; i < textBox.size(); i++)
	{
		if (textBox[i].name == "one")
		{
			textBox[i].highlighted = true;
			userInput = textBox[i].getText();
		}
	}
}

void Menu::textBoxPLayerTwo()
{
	for (int i = 0; i < textBox.size(); i++)
	{
		if (textBox[i].name == "two")
		{
			textBox[i].highlighted = true;
			userInput = textBox[i].getText();
		}
	}
}

void Menu::PlayerOneUCT()
{
	PlayerOneAlgorithm = "UCT";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneUCT")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerOneHuman()
{
	PlayerOneAlgorithm = "human";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneHuman")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerOneGreedy()
{
	PlayerOneAlgorithm = "greedy";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneGreedy")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerOneHeavy()
{
	PlayerOneAlgorithm = "heavy";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneHeavy")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerOneVisited()
{
	PlayerOneAlgorithm = "visited";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneVisited")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerOneReward()
{
	PlayerOneAlgorithm = "reward";
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		if (PlayerOne[i].name == "oneReward")
		{
			PlayerOne[i].selected = true;
		}
		else
		{
			PlayerOne[i].selected = false;
		}
	}
}
void Menu::PlayerTwoUCT()
{
	PlayerTwoAlgorithm = "UCT";
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		if (PlayerTwo[i].name == "twoUCT")
		{
			PlayerTwo[i].selected = true;
		}
		else
		{
			PlayerTwo[i].selected = false;
		}
	}
}
void Menu::PlayerTwoGreedy()
{
	PlayerTwoAlgorithm = "greedy";
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		if (PlayerTwo[i].name == "twoGreedy")
		{
			PlayerTwo[i].selected = true;
		}
		else
		{
			PlayerTwo[i].selected = false;
		}
	}
}
void Menu::PlayerTwoHeavy()
{
	PlayerTwoAlgorithm = "heavy";
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		if (PlayerTwo[i].name == "twoHeavy")
		{
			PlayerTwo[i].selected = true;
		}
		else
		{
			PlayerTwo[i].selected = false;
		}
	}
}
void Menu::PlayerTwoVisited()
{
	PlayerTwoAlgorithm = "visited";
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		if (PlayerTwo[i].name == "twoVisited")
		{
			PlayerTwo[i].selected = true;
		}
		else
		{
			PlayerTwo[i].selected = false;
		}
	}
}
void Menu::PlayerTwoReward()
{
	PlayerTwoAlgorithm = "reward";
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		if (PlayerTwo[i].name == "twoReward")
		{
			PlayerTwo[i].selected = true;
		}
		else
		{
			PlayerTwo[i].selected = false;
		}
	}
}

void Menu::Done()
{
	for (int i = 0; i < but.size(); i++)
	{
		if (but[i].name == "done" && but[i].selected == true)
		{
			m_GameState = gameStart;
		}
	}
}

void Menu::gameMain(sf::RenderWindow& window, int mX, int mY)
{
	switch (m_GameState)
	{
	case Menu::NewGame:
		game->gameMain(window, mX, mY);
		if (BackToMenu == true)
		{
			m_GameState = menu;
			delete game;
			game = NULL;
		}
		break;

	default:
		BackToMenu = false;
		for (int i = 0; i < but.size(); i++)
		{
			if (but[i].name == "done")
			{
				but[i].highlighted = false;
			}
			else if (but[i].withInButtonBounds(mX, mY) == true)
			{
				but[i].highlighted = true;
			}
			else
			{
				but[i].highlighted = false;
			}
				
		}
		for (int i = 0; i < PlayerOne.size(); i++)
		{
			if (PlayerOne[i].withInButtonBounds(mX, mY) == true)
			{
				PlayerOne[i].highlighted = true;
			}
			else
			{
				PlayerOne[i].highlighted = false;
			}

		}

		for (int i = 0; i < PlayerTwo.size(); i++)
		{
			if (PlayerTwo[i].withInButtonBounds(mX, mY) == true)
			{
				PlayerTwo[i].highlighted = true;
			}
			else
			{
				PlayerTwo[i].highlighted = false;
			}
		}
		std::function<void(void)> connect4Game = std::bind(&Menu::connect, this);
		std::function<void(void)> checkers     = std::bind(&Menu::Checkers, this);
		std::function<void(void)> TextBoxOne   = std::bind(&Menu::textBoxPLayerOne, this);
		std::function<void(void)> TextBoxTwo   = std::bind(&Menu::textBoxPLayerTwo, this);

		std::function<void(void)> UCTOne       = std::bind(&Menu::PlayerOneUCT, this);
		std::function<void(void)> Human        = std::bind(&Menu::PlayerOneHuman, this);
		std::function<void(void)> GreedyOne    = std::bind(&Menu::PlayerOneGreedy, this);
		std::function<void(void)> HeavyOne     = std::bind(&Menu::PlayerOneHeavy, this);
		std::function<void(void)> VisitedOne   = std::bind(&Menu::PlayerOneVisited, this);
		std::function<void(void)> RewardOne    = std::bind(&Menu::PlayerOneReward, this);

		std::function<void(void)> UCTTwo       = std::bind(&Menu::PlayerTwoUCT, this);
		std::function<void(void)> GreedyTwo    = std::bind(&Menu::PlayerTwoGreedy, this);
		std::function<void(void)> HeavyTwo     = std::bind(&Menu::PlayerTwoHeavy, this);
		std::function<void(void)> VisitedTwo   = std::bind(&Menu::PlayerTwoVisited, this);
		std::function<void(void)> RewardTwo    = std::bind(&Menu::PlayerTwoReward, this);

		std::function<void(void)> Done = std::bind(&Menu::Done, this);
	

		switch (m_GameState)
		{
		case Menu::menu:
			but.push_back(Button(sf::Vector2i(25, 200), checkers, tex.getRef("CheckerButton"), tex.getRef("CheckerButtoninv"), ""));
			but.push_back(Button(sf::Vector2i(450, 200), connect4Game, tex.getRef("c4Button"), tex.getRef("c4Buttoninv"), ""));
			m_GameState = wait;
			break;
		case Menu::start:
			but.clear();
			text.setString("Pick your settings");
			player1.setString("Player One");
			player2.setString("Player Two");
			iterations.setString("Iterations");
			
			PlayerOne.push_back(Button(sf::Vector2i(50, 200), UCTOne, tex.getRef("Button"), tex.getRef("Buttoninv"), "UCT", "oneUCT"));
			PlayerOne.push_back(Button(sf::Vector2i(50, 300), Human, tex.getRef("Button"), tex.getRef("Buttoninv"), "Human", "oneHuman"));
			PlayerOne.push_back(Button(sf::Vector2i(50, 400), GreedyOne, tex.getRef("Button"), tex.getRef("Buttoninv"), "Greedy", "oneGreedy"));
			PlayerOne.push_back(Button(sf::Vector2i(50, 500), HeavyOne, tex.getRef("Button"), tex.getRef("Buttoninv"), "Heavy", "oneHeavy"));
			PlayerOne.push_back(Button(sf::Vector2i(50, 600), VisitedOne, tex.getRef("Button"), tex.getRef("Buttoninv"), "Visited", "oneVisited"));
			PlayerOne.push_back(Button(sf::Vector2i(175, 200), RewardOne, tex.getRef("Button"), tex.getRef("Buttoninv"), "Reward", "oneReward"));

			PlayerTwo.push_back(Button(sf::Vector2i(575, 200), UCTTwo, tex.getRef("Button"), tex.getRef("Buttoninv"), "UCT", "twoUCT"));
			PlayerTwo.push_back(Button(sf::Vector2i(575, 300), GreedyTwo, tex.getRef("Button"), tex.getRef("Buttoninv"), "Greedy", "twoGreedy"));
			PlayerTwo.push_back(Button(sf::Vector2i(575, 400), HeavyTwo, tex.getRef("Button"), tex.getRef("Buttoninv"), "Heavy", "twoHeavy"));
			PlayerTwo.push_back(Button(sf::Vector2i(575, 500), VisitedTwo, tex.getRef("Button"), tex.getRef("Buttoninv"), "Visited", "twoVisited"));
			PlayerTwo.push_back(Button(sf::Vector2i(575, 600), RewardTwo, tex.getRef("Button"), tex.getRef("Buttoninv"), "Reward", "twoReward"));

			
			but.push_back(Button(sf::Vector2i(303, 500), Done, tex.getRef("DoneInv"), tex.getRef("Done"), "", "done"));
			textBox.push_back(Button(sf::Vector2i(50, 100), TextBoxOne, tex.getRef("TextBoxinv"), tex.getRef("TextBox"), "", "one"));
			textBox.push_back(Button(sf::Vector2i(575, 100), TextBoxTwo, tex.getRef("TextBoxinv"), tex.getRef("TextBox"), "", "two"));

		
			m_GameState = wait;
			break;
		case Menu::gameStart:
			createGame(window);
			but.clear();
			PlayerOne.clear();
			PlayerTwo.clear();
			textBox.clear();
			text.setString("");
			player1.setString("");
			player2.setString("");
			iterations.setString("");
			m_GameState = NewGame;
			break;
		case Menu::NewGame:

			break;
		case Menu::wait:
			if (GameToBePlayed != "" && PlayerOneAlgorithm != "" && PlayerTwoAlgorithm != "")
			{
				bool gameReady = false;
				for (int i = 0; i < textBox.size(); i++)
				{
					if (textBox[i].name == "one")
					{
						if (textBox[i].getText() != "" && textBox[i].getText() != "0")
						{
							gameReady = true;
						}
						else
						{
							gameReady = false;
						}
					}
				}
				if (gameReady)
				{
					for (int i = 0; i < textBox.size(); i++)
					{
						if (textBox[i].name == "two")
						{
							if (textBox[i].getText() != "" && textBox[i].getText() != "0")
							{
								gameReady = true;
							}
							else
							{
								gameReady = false;
							}
						}
					}
				}
				if (gameReady)
				{
					for (int i = 0; i < but.size(); i++)
					{
						if (but[i].name == "done" )
						{
							but[i].selected = true;
						}		
					}
				}
				else
				{
					for (int i = 0; i < but.size(); i++)
					{
						if (but[i].name == "done")
						{
							but[i].selected = false;
						}
					}
				}
			}
			break;
		default:
			break;
		}

		for (int i = 0; i < textBox.size(); i++)
		{
			if (textBox[i].highlighted == true)
			{
				textBox[i].setText(userInput);
				if (textBox[i].getText().size() > 3 && std::stoi(textBox[i].getText()) > 1000)
				{
					userInput = "1000";
				}
			}
		}
		draw(window);
		click = false;
	break;
	}
	

	
}

void Menu::draw(sf::RenderWindow &window)
{
	sf::Texture pTexBackground = tex.getRef("background");
	sf::Sprite sprite;
	sprite.setTexture(pTexBackground);
	window.draw(sprite);
	for (int i = 0; i < but.size(); i++)
	{
		but.at(i).render(window);
	}
	for (int i = 0; i < PlayerOne.size(); i++)
	{
		PlayerOne.at(i).render(window);
	}
	for (int i = 0; i < PlayerTwo.size(); i++)
	{
		PlayerTwo.at(i).render(window);
	}
	for (int i = 0; i < textBox.size(); i++)
	{
		textBox.at(i).render(window);
	}
	window.draw(text);
	window.draw(player1);
	window.draw(player2);
	iterations.setPosition(sf::Vector2f(50, 75));
	window.draw(iterations);
	iterations.setPosition(sf::Vector2f(575, 75));
	window.draw(iterations);
	
}
void Menu::createGame(sf::RenderWindow& window)
{
	connect4game::Player player1;
	connect4game::Player player2;
	int playerOneIt;
	int playertwoIt;

	for (int i = 0; i < textBox.size(); i++)
	{
		if (textBox[i].name == "one")
		{
			playerOneIt = std::stoi(textBox[i].getText());
		}
		if (textBox[i].name == "two")
		{
			playertwoIt = std::stoi(textBox[i].getText());
		}
	}
	if (PlayerOneAlgorithm == "UCT")
	{
		player1 = connect4game::UCTplayer;
	}
	else if (PlayerOneAlgorithm == "human")
	{
		player1 = connect4game::human;
	}
	else if (PlayerOneAlgorithm == "greedy")
	{
		player1 = connect4game::Greedy;
	}
	else if (PlayerOneAlgorithm == "heavy")
	{
		player1 = connect4game::heavy;
	}
	else if (PlayerOneAlgorithm == "visited")
	{
		player1 = connect4game::visited;
	}
	else if (PlayerOneAlgorithm == "reward")
	{
		player1 = connect4game::reward;
	}
	if (PlayerTwoAlgorithm == "UCT")
	{
		player2 = connect4game::UCTplayer;
	}
	else if (PlayerTwoAlgorithm == "greedy")
	{
		player2 = connect4game::Greedy;
	}
	else if (PlayerTwoAlgorithm == "heavy")
	{
		player2 = connect4game::heavy;
	}
	else if (PlayerTwoAlgorithm == "visited")
	{
		player2 = connect4game::visited;
	}
	else if (PlayerTwoAlgorithm == "reward")
	{
		player2 = connect4game::reward;
	}
	if (GameToBePlayed == "connect")
	{
		
		game = new connect4game(window, player1, player2, playerOneIt, playertwoIt);
	}
	else if (GameToBePlayed == "checkers")
	{
		game = new checkerGame(window, player1, player2, playerOneIt, playertwoIt);
	}
}
