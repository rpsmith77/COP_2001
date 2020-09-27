/******************************************************************************
* File:		snake.h
* Author:	Ryan Smith
* Class:	COP 2001 200205
* Purpose:	header file w/ program definitions for a snake class for a snake game
			where the snake moves around the screen and grows when it eats
******************************************************************************/
#ifndef SNAKE_H
#define SNAKE_H

#include "block.h"
#include "snakedefs.h"

class Snake
{
public:
	//-----------------------------------------------------------------------------
	// consturctors
	//-----------------------------------------------------------------------------
	Snake();	// default

	//-----------------------------------------------------------------------------
	// accessors (getters and setters)
	//-----------------------------------------------------------------------------
	Block* getHead();
	Block* getTail();
	int	   getSize();
	float  getDistance();

	Direction getCurrent();
	Direction getNext();
	void	  setNext(Direction value);

	//----------------------------------------------------------------------------
	// member methods
	//----------------------------------------------------------------------------
	bool isMoving();
	void turn();
	void move(float distance);
	bool hasMoved();
	void reset();
	bool hitSelf();
	bool hitBlock(Block* block, bool all = false);
	void grow();
	void draw(OpenGL& window);

private:
	
	Block head;				// root of snake
	Block* tail;			// tail of snake
	int size;				// how big the snake has grown (starts at 1)
	float distance;			// distance snake has travled since last full block
	Direction current;		// current direction snake is traveling
	Direction next;			// next direction user has inputed
};

#endif // !SNAKE_H
