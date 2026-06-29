/** \file node.h
* Header file for the node class.
*/


#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <array>
#include <time.h>

//! The node class

/*!
* This class contains the node strucher this is main class of monte carlo tree search
* This class users left child right sibling as its tree strucher.
*/
template <typename tState, typename possibleMoves>

class node : public std::enable_shared_from_this<node<tState, possibleMoves>> // allows this in shared pointer form
{
private:	
	/**  A typedef int of the potental moves of the state this may be changed for differant games*/
	//typedef int possibleMoves;

		//data for the strucher
		/** A shared pointer to the sibling on the right*/
		std::shared_ptr<node<tState, possibleMoves>> sibling;
		/** A shared pointer to the left child*/
		std::shared_ptr<node<tState, possibleMoves>> child;
		/** A weak pointer to the parent has to be weak to stop circular dependeny*/
		std::weak_ptr<node<tState, possibleMoves>> parent;
		/** the state of the game*/
		tState state;               // will store the state
		/** the current move of the node*/
		possibleMoves currentMove;

		//value
		/** the amount of visits the node has*/
		int visits;
		/** the total value accumulated from the rewards given to the node*/
		double Value;
		/** the uct score of the node*/
		double score;
		/** the total number of children a node has*/
		int children;

public:
	/** a vector of potential moves for this nodes children */
	std::vector<possibleMoves> pMoves; //used to make children

	/**
	The root constructor of a node.
	\param data is the state of the game.
	*/
	node(const tState &data)
	{ // Constructor
		state = data;
		//currentMove = NULL;
		pMoves = state.getMoves(state.getPlayer()); // #TODO how to set templated player
		children = pMoves.size() -1;
		visits = 0;
		Value = 0;
		
	}

	/**
	The root constructor of a node.
	\param data is the state of the game.
	\param current move of this node the transitional move of the parent to get to this node.
	\param par is the pointer to the parent node.
	*/
	node(const tState &data, const possibleMoves &currMove, std::shared_ptr<node<tState, possibleMoves>> par)
	{ // Constructor
		state = data;
		parent = par;
		pMoves = state.getMoves(state.getPlayer());
		currentMove = currMove;
		children = pMoves.size()-1;
		visits = 0;
		Value = 0;
		state.getPlayer();
		
	}
	/**
	The deconstructor of a node.
	*/
	~node() {}
	/** get the node state*/
	tState nodeState()
	{
		return state;
	}
	/** checks if the node has a child*/
	bool hasChild()                    // True if node is a leaf
	{
		if (this->getChild() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
		
	}
	/** get the last child from the parent*/
	std::shared_ptr<node<tState, possibleMoves>> getLastChild()
	{
		if (this->hasChild() == true)
		{
			std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
			std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();
			while (temp2 != nullptr)
			{
				temp = temp->getSibling();
				temp2 = temp->getSibling();
			}

		
			return temp;
		}
		else
		{
			return nullptr;
		}
	}
	/**
	get the child at the position wanted
	\param The wanted child at the said integer.
	*/
	std::shared_ptr<node<tState, possibleMoves>> getSaidChild(int wantedChild)
	{
		if (this->hasChild() == true)
		{
			std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();

			for (int i = 0; i < wantedChild; i++)
			{
				temp = temp->getSibling();
			}
			return temp;
		}
	}
	/** 
	get the parent
	*/
	std::weak_ptr<node<tState, possibleMoves>> getParent()
	{
		return parent;
	}
	/**
	get the left most child of the parent
	*/
	std::shared_ptr<node<tState, possibleMoves>> getChild()
	{
		return child;
	}
	/**
	get the next right sibling
	*/
	std::shared_ptr<node<tState, possibleMoves>> getSibling()
	{
		return sibling;
	}

	/**
	get the current move of the state
	*/
	possibleMoves getCurrentMove()
	{
		return currentMove;
	}
	/**
	set the parent of the node
	\param A pointer to the parent you want to set
	*/
	void setParent(std::shared_ptr<node<tState, possibleMoves>> par)
	{
		parent = par;
	}
	/**
	set the right sibling of the node
	\param A pointer to the sibling you want to set
	*/
	void setSibling(std::shared_ptr<node<tState, possibleMoves>> sib)
	{
		sibling = sib;
	}
	/**
	set the child of the node
	\param A pointer to the child you want to set
	*/
	void setChild(std::shared_ptr<node<tState, possibleMoves>> chil)
	{
		child = chil;
	}
	/**
	adds a node to the tree
	\param the state of the new board
	\param the move which set the new board
	*/
	std::shared_ptr<node<tState, possibleMoves>> addNode(const tState& state, possibleMoves m)
	{
		std::shared_ptr<node<tState, possibleMoves>> n = std::make_shared<node<tState, possibleMoves>>(node<tState, possibleMoves>(state, m, shared_from_this()));

		if (this->hasChild() == true)
		{
			std::shared_ptr<node<tState, possibleMoves>> temp = this->getLastChild();
			temp->sibling = n;
		}
		else
		{
			this->child = n;
		}

		pMoves.erase(std::remove(pMoves.begin(), pMoves.end(), m), pMoves.end()); //remove the move from parent

		return n;
	}
	/**
	checks if there is any possible moves left for the node
	*/
	bool fullyExpanded()
	{
		return pMoves.empty();
	}
	/**
	sets the uct score of the node
	*/
	void uctScore()
	{
		if (visits != 0)
		{
			 score = Value / double(visits) + (2 * (1 / std::sqrt(2.0))) * (std::sqrt(2.0 * std::log(double(this->parent.lock()->visits)) / visits));
		}
	}
	/**
	 updates the visits and value of the node
	 \param the result of the terminal node
	*/
	void update(double result)
	{
		visits++;
		Value = Value + result;
	}
	/**
	randomly picks the next move
	*/
	possibleMoves getNextMove()
	{
		std::srand(time(NULL));
		int v1 = std::rand() % (pMoves.size());
		//int v1 = pMoves.size();
		if (v1 != 0)
		{
			v1 -= 1;
		}
		return pMoves.at(v1);
	}
	/**
	goes thought the children of the parent and selects the most visited child
	*/
	std::shared_ptr<node<tState, possibleMoves>> bestChildFindByVisits()
	{
		std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
		if (temp->getSibling() != nullptr)
		{
			std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();

			while (temp2 != nullptr)
			{
				if (temp->visits < temp2->visits)
				{
					temp = temp2;
					temp2 = temp->getSibling();
				}
				else
				{
					temp2 = temp2->getSibling();
				}
			}
		}
		
		return temp;
	}
	/**
	goes thought the children of the parent and selects the heaviest child weight = value / visits
	*/
	std::shared_ptr<node<tState, possibleMoves>> bestChildFindbyWeight()
	{
		std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
		std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();
		int check = 0;
		while (temp2 != nullptr)
		{
			if (temp->weight() < temp2->weight())
			{
				temp = temp2;
				temp2 = temp->getSibling();
			}
			else
			{
				temp2 = temp2->getSibling();
			}
			check++;
		}
		return temp;
	}
	/**
	goes thought the children of the parent and selects highest value child
	*/
	std::shared_ptr<node<tState, possibleMoves>> selectHighestRewardChild()
	{
		std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
		std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();
		while (temp2 != nullptr)
		{
			if (temp->Value < temp2->Value)
			{
				temp = temp2;
				temp2 = temp->getSibling();
			}
			else
			{
				temp2 = temp2->getSibling();
			}
		}
		return temp;
	}
	/**
	goes thought the children of the parent and selects highest value childbut can also randomly explore a new node. known as greedy monte carlo
	*/
	std::shared_ptr<node<tState, possibleMoves>> selectBestChildWithExplore()
	{
		int rand = std::rand() % 10;
		std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
		if (rand < 6)
		{
			
			std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();

			while (temp2 != nullptr)
			{
				if (temp->Value < temp2->Value)
				{
					temp = temp2;
					temp2 = temp->getSibling();
				}
				else
				{
					temp2 = temp2->getSibling();
				}
			}

			return temp;
		}
		else
		{
			int ChildCount = 0;
			while (temp != nullptr)
			{
				temp = temp->getSibling();
				ChildCount++;
			}

			temp = this->getChild();
			int v1 = std::rand() % (ChildCount);
			for (int i = 0; i < v1; i++)
			{
				temp = temp->getSibling();
			}
			return temp;
		}


	}
	/**
	selects the child withe the greatest score using the uct algorithm
	*/
	std::shared_ptr<node<tState, possibleMoves>> selectBestChildWithUCT()
	{

		std::shared_ptr<node<tState, possibleMoves>> temp = this->getChild();
		std::shared_ptr<node<tState, possibleMoves>> temp2 = temp->getSibling();
		
		while (temp != nullptr)
		{
			temp->uctScore();
			temp = temp->getSibling();
		}

		temp = this->getChild();

		while (temp2 != nullptr)
		{
			if (temp->score < temp2->score)
			{
				temp = temp2;
				temp2 = temp->getSibling();
			}
			else
			{
				temp2 = temp2->getSibling();
			}
		}

		return temp;
	}
	/**
	calculates the weight of the node
	*/
	double weight()
	{
		return Value / visits;
	}
};

#endif NODE_H