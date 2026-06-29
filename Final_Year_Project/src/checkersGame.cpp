#include "checkerGame.h"
#include "menu.h"

checkerGame::checkerGame(sf::RenderWindow& rw, connect4game::Player PlayerOne, connect4game::Player PlayerTwo, int playerOneIterations, int playerTwoIterations)
{
	player1 = PlayerOne;
	player2 = PlayerTwo;

	PlayerOneIterations = playerOneIterations;
	PlayerTwoIterations = playerTwoIterations;



	highlight = false;
	highlightX = 0;
	highlightY = 0;

	PlayerOneWins = 0;
	PlayerTwoWins = 0;
	draws = 0;

	//setm_background("images/starfield1.png", 100);
	m_win = &rw;
	if (!tex.loadTexture("background", "images/cool.png"))
	{
		std::cout << "error file background 1 not loaded";
	}

	if (!tex.loadTexture("player1", "images/CheckerWhite.png"))
	{
		std::cout << "error file player 1 not loaded";
	}

	if (!tex.loadTexture("player1King", "images/CheckerWhiteKing.png"))
	{
		std::cout << "error file player 1 not loaded";
	}

	if (!tex.loadTexture("player2", "images/CheckerBlack.png"))
	{
		std::cout << "error file player 2 not loaded";
	}

	if (!tex.loadTexture("player2King", "images/CheckerBlackKing.png"))
	{
		std::cout << "error file player 2 not loaded";
	}

	if (!tex.loadTexture("square1", "images/rectOne.png"))
	{
		std::cout << "error file empty not loaded";
	}

	if (!tex.loadTexture("square2", "images/rectTwo.png"))
	{
		std::cout << "error file empty not loaded";
	}

	if (!tex.loadTexture("highlight", "images/rectHighLighted.png"))
	{
		std::cout << "error file highlight not loaded";
	}
	if (!tex.loadTexture("mouse", "images/gameCursor.png"))
	{
		std::cout << "error file highlight not loaded";
	}
	con4State.setPlayer(1);
	con4State.setStartingPlayer(1);
	con4State.clearCurrentBoard();
	con4State.SetUpCurrentBoard();
	drawFlag = true;

	//m_background.setTexture(tex.getRef("background"));
	m_GameState = checkerGame::Intro;
}

void checkerGame::keyEvent(std::string skeyPressed)
{
	if (skeyPressed.compare("SPACE") == 0 && m_GameState == checkerGame::Wait)
	{
		m_GameState = Restart;
	}

}

void checkerGame::gameMain(sf::RenderWindow& window, int mX, int mY)
{
	loadLevel(mX, mY);
	player1Score.set(125, 635, "Player One Wins " + std::to_string(PlayerOneWins), 20);
	Player2Score.set(510, 635, "Player Two Wins " + std::to_string(PlayerTwoWins), 20);
	draw.set(350, 635, "draws " + std::to_string(draws), 20);
	if (m_GameState == checkerGame::Intro)
	{
		m_GameState = checkerGame::level;
	}

	else if (m_GameState == checkerGame::level)
	{
		if (con4State.getBoard().terminal())
		{
			m_GameState = checkerGame::GAME_OVER;

		}
		else if (con4State.getBoard().gameTerminal(con4State.getBoard().getMoves(1).size(), con4State.getBoard().getMoves(2).size()) && drawn)
		{
			m_GameState = checkerGame::GAME_OVER;

		}

		else if (con4State.getfinalplayer() == 1)
		{
			std::vector<int> moves;
			switch (player1)
			{
			case connect4game::human:
				drawn = false;
				break;
			case connect4game::UCTplayer:

				con4State.setStartingPlayer(1);
				moves = UCTTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::Greedy:

				con4State.setStartingPlayer(1);
				moves = mtcsTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::heavy:
				con4State.setStartingPlayer(1);
				moves = weigtedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::visited:
				con4State.setStartingPlayer(1);
				moves = visitedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::reward:
				con4State.setStartingPlayer(1);
				moves = rewardTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			default:
				break;
			}
		}

		else if (drawn && con4State.getfinalplayer() == 2 && drawn == true)
		{
			std::vector<int> moves;
			switch (player2)
			{
			case connect4game::human:
				drawn = false;
				break;
			case connect4game::UCTplayer:

				con4State.setStartingPlayer(2);
				moves = UCTTree.runTree(con4State.getBoard(), PlayerTwoIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::Greedy:

				con4State.setStartingPlayer(2);
				moves = mtcsTree.runTree(con4State.getBoard(), PlayerTwoIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::heavy:
				con4State.setStartingPlayer(2);
				moves = weigtedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::visited:
				con4State.setStartingPlayer(2);
				moves = visitedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			case connect4game::reward:
				con4State.setStartingPlayer(2);
				moves = rewardTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(moves);
				drawn = false;
				break;
			default:
				break;
			}
		}
	}

	else if (m_GameState == checkerGame::GAME_OVER)// remove all and set up for another session
	{
		bool player1HasCounters = false;
		bool player2HasCounters = false;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (con4State.currentStateAccess(i, j) == 1 || con4State.currentStateAccess(i, j) == 3)
				{
					player1HasCounters = true;
				}
				if (con4State.currentStateAccess(i, j) == 2 || con4State.currentStateAccess(i, j) == 4)
				{
					player2HasCounters = true;
				}
				if (player1HasCounters && player2HasCounters)
				{
					break;
				}
			}
		}
		int score = 0;
		if (player1HasCounters == true && player2HasCounters == false)
		{
			score = 1;
		}
		else if (player1HasCounters == false && player2HasCounters == true)
		{
			score = 2;
		}

		//gameOver.set(260, 300, "GameOver");
		if (score == 1)
		{
			gameOver.set(250, 300, "Player one won");
			PlayerOneWins++;
		}
		else if (score == 0)
		{
			gameOver.set(250, 300, "GameOver  Draw");
			draws++;
		}
		else if (score == 2)
		{
			gameOver.set(250, 300, "Player two won");
			PlayerTwoWins++;
		}

		pressSpace.set(128, 350, "Press Space To Continue");
		m_GameState = checkerGame::Wait;
	}
	else if (m_GameState == checkerGame::Wait)
	{
		pressSpace.set(128, 350, "Press Space To Continue");
	}
	else if (m_GameState == checkerGame::Restart)// remove all and set up for another session
	{
		con4State.clearCurrentBoard();
		con4State.SetUpCurrentBoard();
		con4State.setPlayer(1);
		m_GameState = level;
	}

	for (m_GameObjectit = m_GameObs.begin(); m_GameObjectit != m_GameObs.end(); ++m_GameObjectit)
	{
		m_GameObjectit->get()->draw(window);
	}

	m_GameObs.clear();
	player1Score.draw(window, sf::Color(255, 255, 255));
	Player2Score.draw(window, sf::Color(255, 255, 255));
	draw.draw(window, sf::Color(255, 255, 255));
	if (m_GameState == checkerGame::Wait)
	{
		gameOver.draw(window, sf::Color(255, 255, 255));
		pressSpace.draw(window, sf::Color(255, 255, 255));
	}
	
	drawFlag = true;

	drawn = true;
}

void checkerGame::loadLevel(int mX, int mY)
{
	sf::Texture pTexSquare1 = tex.getRef("square1");
	sf::Texture pTexSquare2 = tex.getRef("square2");
	sf::Texture pTexHighlight = tex.getRef("highlight");

	sf::Texture pTex1 = tex.getRef("player1");
	sf::Texture pTex1King = tex.getRef("player1King");

	sf::Texture pTex2 = tex.getRef("player2");
	sf::Texture pTex2King = tex.getRef("player2King");

	sf::Texture pTexHigh = tex.getRef("highlight");

	sf::Texture pTexBackground = tex.getRef("background");

	checkerState temp = con4State.getBoard();
	int windowWidth = (m_win->getSize().x / 2)- 240;
	int windowHeight = (m_win->getSize().y / 2) + 250;
	bool switcher = false;
	m_GameObs.push_back(std::shared_ptr<circle>(new circle(m_win->getSize().x /2, m_win->getSize().y/2, pTexBackground)));
	int counter = 0;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (switcher)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight -(70 * j), pTexSquare1)));
				switcher = false;
			}
			else
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight -(70 * j), pTexSquare2)));
				switcher = true;
			}
			counter++;

			if (highlight)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * highlightX), windowHeight - (70 * highlightY), pTexHighlight)));
			}

			if (counter > 7)
			{
				if (switcher)
				{
					switcher = false;
				}
				else
				{
					switcher = true;
				}
				counter = 0;
			}
			if (temp.stateAccess(i, j) == 1)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight - (70 * j), pTex1)));
			}
			else if (temp.stateAccess(i, j) == 2)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight - (70 * j), pTex2)));
			}
			else if (temp.stateAccess(i, j) == 3)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight - (70 * j), pTex1King)));
			}
			else if (temp.stateAccess(i, j) == 4)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle(windowWidth + (70 * i), windowHeight - (70 * j), pTex2King)));
			}
		}
	}

}

void checkerGame::clickEvent(int x, int y)
{
	if (con4State.getfinalplayer() == 1)
	{
		int windowWidth = (m_win->getSize().x / 2) - 240;
		int windowHeight = (m_win->getSize().y / 2) + 250;
		if (x > m_win->getSize().x / 2 - 290 && x < m_win->getSize().x / 2 + 290)
		{
			if (y < m_win->getSize().y / 2 + 290 && y > m_win->getSize().y / 2 - 290)
			{
				if ((con4State.getBoard().stateAccess(int((x - 123) / 70), int((560 - y + 74) / 70)) == 1 || con4State.getBoard().stateAccess(int((x - 123) / 70), int((560 - y + 74) / 70)) == 3) && m_GameState != checkerGame::GAME_OVER)
				{
					//con4State.setFinalMove(x / windowWidth); #TODO
					highlightX = (x - 123) / 70;
					highlightY = (560 - y + 74) / 70;
					highlight = true;
				}
				if (con4State.getBoard().stateAccess(int((x - 123) / 70), int((560 - y + 74) / 70)) == 0 && m_GameState != checkerGame::GAME_OVER && highlight)
				{
					std::vector<int> moves;
					moves.push_back(highlightX);
					moves.push_back(highlightY);

					highlightX = (x - 123) / 70;
					highlightY = (560 - y + 74) / 70;

					moves.push_back(int((x - 123) / 70));
					moves.push_back(int((560 - y + 74) / 70));
					int checkMoves = CheckValidMove(moves);
					if (checkMoves == 1)
					{
						con4State.setFinalMove(moves);// #TODO
					}
					else if (checkMoves == 2)
					{
						con4State.setFinalMoveStep(moves);
					}					
				
					highlight = false;
				}
			}
		}
		//windowWidth + (70 * i), windowHeight - (70 * j);
		

		drawn = false;
	}
}

int checkerGame::CheckValidMove(const std::vector<int> &moves)
{
	std::vector<Move> allMoves = con4State.getBoard().getMoves(1);
	for (int i = 0; i < allMoves.size(); i++)
	{
		Move move = allMoves.at(i);
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves.at(i) != move.at(i))
			{
				break;
			}
			else if (i == moves.size() - 1 && moves.size() == move.size())
			{
				return 1;
			}
			else if (i == moves.size() - 1)
			{
				return 2;
			}
		}
	}
	return 0;
}

void checkerGame::addcircle(unsigned int column, int player)
{

}