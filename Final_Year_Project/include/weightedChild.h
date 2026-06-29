/** \file WeightedChild.h
* Header file for the WeightedChild class.
*/

#ifndef WEIGHTEDCHILD_H
#define WEIGHTEDCHILD_H


#include <memory>
#include <math.h>
#include "node.h"
#include <iostream>
//! The WeightedChild class

/*!
This class contains the WeightedChild program.
*/

template <typename tState, typename move>
class WeightedChild

{
private:
	/**  A typedef int of the potental moves of the state this may be changed for differant games*/
	//typedef int move;
	/**  A shared pointer to the root node*/
	std::shared_ptr<node<tState, move>> root;

public:
	/** The default construter displays the score and text.*/
	WeightedChild()
	{ // Constructor

	}
	/** returns the root node.*/
	std::shared_ptr<node<tState, move>> returnRoot()
	{
		return root;
	}
	/** sets the new root node.*/
	void newroot(const tState& value)
	{
		root = std::make_shared<node<tState, move>>(node<tState, move>(value));
	}
	/** sets the new root node.
	/param rootstate the current state of the game boared
	/param iterations the amount of times you want the mcts to run
	*/
	move runTree(tState rootstate, int iterations)
	{
		newroot(rootstate);
		std::shared_ptr<node<tState, move>> nod;
		tState st;

		for (int i = 0; i < iterations; i++)
		{
			nod = returnRoot();
			st = nod->nodeState();

			// selection process
			while (nod->fullyExpanded() == true && nod->hasChild() == true) //fully expanded and not a leaf
			{
				//select child
				nod = nod->bestChildFindbyWeight();

				//commit the move
				st.doMove(nod->getCurrentMove());
			}

			// expansion
			if (!nod->fullyExpanded())
			{
				//get the next move
				move mov = nod->getNextMove();
				st.doMove(mov);
				nod = nod->addNode(st, mov); //add node breaking
			}

			//simulate

			st.simulate();

			//backpropergrate
			while (nod != NULL)
			{
				nod->update(st.outcome());
				nod = nod->getParent().lock();
			}

		}

		std::shared_ptr<node<tState, move>> root = returnRoot();
		return root->bestChildFindByVisits()->getCurrentMove();
	}

};

#endif WEIGHTEDCHILD_H