#include "connect4game.h"


connect4game::connect4game(sf::RenderWindow& rw, Player PlayerOne, Player PlayerTwo, int playerOneIterations, int playerTwoIterations)
{
	player1 = PlayerOne;
	player2 = PlayerTwo;
	PlayerOneIterations = playerOneIterations;
	PlayerTwoIterations = playerTwoIterations;
	//setm_background("images/starfield1.png", 100);
	m_win = &rw;
	//tex.loadTexture("background", "images/background.png");

	if (!tex.loadTexture("player1", "images/player1.png"))
	{
		std::cout << "error file player 1 not loaded";
	}

	if (!tex.loadTexture("player2", "images/player2.png"))
	{
		std::cout << "error file player 2 not loaded";
	}
	

	if (!tex.loadTexture("empty", "images/empty.png"))
	{
		std::cout << "error file empty not loaded";
	}
	

	if (!tex.loadTexture("highlight", "images/highlight.png"))
	{
		std::cout << "error file highlight not loaded";
	}
	con4State.setPlayer(1);
	drawFlag = true;
	
	//m_background.setTexture(tex.getRef("background"));
	m_GameState = connect4game::Intro;
}

void connect4game::keyEvent(std::string skeyPressed)
{
	if (skeyPressed.compare("SPACE") == 0 && m_GameState == connect4game::GAME_OVER)
	{
		m_GameState = Restart;
	}
}

void connect4game::gameMain(sf::RenderWindow& window ,int mX, int mY)
{
	loadLevel(mX, mY);

	if (m_GameState == connect4game::Intro)
	{
		m_GameState = connect4game::level;
	}

	else if (m_GameState == connect4game::level)
	{
		if (con4State.getfinalplayer() == 1)
		{
			int move;
			switch (player1)
			{
			case connect4game::human:

				break;
			case connect4game::UCTplayer:
				
				con4State.setStartingPlayer(1);
				move = UCTTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::Greedy:
				
				con4State.setStartingPlayer(1);
				move = mtcsTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::heavy:
				con4State.setStartingPlayer(1);
				move = weigtedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::visited:
				con4State.setStartingPlayer(1);
				move = visitedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::reward:
				con4State.setStartingPlayer(1);
				move = rewardTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			default:
				break;
			}

			
		}
		else if (drawn && con4State.getfinalplayer() == 2)
		{
			switch (player2)
			{
				int move;
			case connect4game::human:

				break;
			case connect4game::UCTplayer:

				con4State.setStartingPlayer(2);
				move = UCTTree.runTree(con4State.getBoard(), PlayerTwoIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::Greedy:

				con4State.setStartingPlayer(2);
				move = mtcsTree.runTree(con4State.getBoard(), PlayerTwoIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::heavy:
				con4State.setStartingPlayer(2);
				move = weigtedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::visited:
				con4State.setStartingPlayer(2);
				move = visitedTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			case connect4game::reward:
				con4State.setStartingPlayer(2);
				move = rewardTree.runTree(con4State.getBoard(), PlayerOneIterations);//do not increase too much cause it to break
				con4State.setFinalMove(move);
				drawn = false;
				break;
			default:
				break;
			}
			
			
		}

		if (con4State.getBoard().terminal())
		{
			m_GameState = connect4game::GAME_OVER;

		}
	}

	else if (m_GameState == connect4game::GAME_OVER)// remove all and set up for another session
	{
		//gameOver.set(260, 300, "GameOver");
		if (con4State.outcome() == 0)
		{
			gameOver.set(160, 300, "GameOver Player one won");
		}
		else if (con4State.outcome() == 0.5)
		{
			gameOver.set(200, 300, "GameOver Draw");
		}
		else if (con4State.outcome() == 1)
		{
			gameOver.set(160, 300, "GameOver Player two won");
		}

		pressSpace.set(70, 350, "Press Space To Continue");
	}

	else if (m_GameState == connect4game::Restart)// remove all and set up for another session
	{
		con4State.clearCurrentBoard();
		con4State.setPlayer(1);
		m_GameState = level;
	}

	for (m_GameObjectit = m_GameObs.begin(); m_GameObjectit != m_GameObs.end(); ++m_GameObjectit)
	{
		m_GameObjectit->get()->draw(window);
	}
	m_GameObs.clear();
	if (m_GameState == connect4game::GAME_OVER)
	{
		gameOver.draw(window);
		pressSpace.draw(window);
	}

	drawFlag = true;
	// leave this line of code here, last in the function.
	//gameMain(sKeyPressed,sKeyReleased,window);
	drawn = true;
}

void connect4game::loadLevel(int mX, int mY)
{
	sf::Texture pTexEmpty = tex.getRef("empty");
	sf::Texture pTex1 = tex.getRef("player1");
	sf::Texture pTex2 = tex.getRef("player2");
	sf::Texture pTexHigh = tex.getRef("highlight");
	c4state temp = con4State.getBoard();
	int windowWidth = m_win->getSize().x / temp.getCols();
	int windowHeight = m_win->getSize().y / temp.getRows();
	


	for (int i = 0; i < temp.getCols(); i++)
	{
		for (int j = 0; j < temp.getRows(); j++)
		{
			if (temp.stateAccess(i,j) == 0)
			{
				if (i * windowWidth < mX && mX < (i + 1) * windowWidth && drawFlag == true)
				{
					m_GameObs.push_back(std::shared_ptr<circle>(new circle((windowWidth * i + 60), m_win->getSize().y - (windowHeight * j + 60), pTexHigh)));
					drawFlag = false;
				}
				else
				{
					m_GameObs.push_back(std::shared_ptr<circle>(new circle((windowWidth * i + 60), m_win->getSize().y - (windowHeight * j + 60), pTexEmpty)));
				}
			}
			else if (temp.stateAccess(i, j) == 1)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle((windowWidth * i + 60), m_win->getSize().y - (windowHeight * j + 60), pTex1)));
			}
			else if (temp.stateAccess(i, j) == 2)
			{
				m_GameObs.push_back(std::shared_ptr<circle>(new circle((windowWidth * i + 60), m_win->getSize().y - (windowHeight * j + 60), pTex2)));
			}
		}
	}


}

void connect4game::clickEvent(int x , int y)
{
	if (con4State.getfinalplayer() == 1)
	{
		c4state temp = con4State.getBoard();
		int windowWidth = m_win->getSize().x / temp.getCols();
		if (con4State.getBoard().stateAccess(x / windowWidth, 5) == 0 && m_GameState != connect4game::GAME_OVER)
		{
			con4State.setFinalMove(x / windowWidth);
		}
		
		drawn = false;
	}
}

void connect4game::addcircle(unsigned int column, int player)
{
	
}