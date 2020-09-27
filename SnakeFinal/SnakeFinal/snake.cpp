/******************************************************************************
* File:		snake.cpp
* Author:	Ryan Smith
* Class:	COP 2001 200205
* Purpose:	implementation file w/ program definitions for a snake class for a snake game
			where the snake moves around the screen and grows when it eats
******************************************************************************/
#include "snake.h"

//-----------------------------------------------------------------------------
// consturctors
//-----------------------------------------------------------------------------
/******************************************************************************
Default constructor
******************************************************************************/
Snake::Snake()
{
	head = Block(WINDOW_WIDTH / 2 + BLOCK_SIZE / 2,
				 WINDOW_HEIGHT / 2 + BLOCK_SIZE / 2,
				 BLOCK_SIZE,
				 BLOCK_SIZE,
				 SNAKE_COLOR);
	tail = &head;
	size = 1;
	current = None;
	next = None;
	distance = 0;
}

//-----------------------------------------------------------------------------
// accessors (getters and setters)
//-----------------------------------------------------------------------------
Block* Snake::getHead() { return &head; }
Block* Snake::getTail() { return tail; }
int	   Snake::getSize() { return size; }
float  Snake::getDistance() { return distance; }

Direction Snake::getCurrent() { return current; }
Direction Snake::getNext() { return next; }
void	  Snake::setNext(Direction value) { next = value; }

//----------------------------------------------------------------------------
// member methods
//----------------------------------------------------------------------------
/******************************************************************************
detrimine if snake has either x or y velocity
parameters: 
	none
returns:
	bool	- true if block moving
******************************************************************************/
bool Snake::isMoving()
{
	return head.isMoving();
}


/******************************************************************************
turn snake based on user input direction
parameters: 
	none
returns:
	void
******************************************************************************/
void Snake::turn()
{

	// adjust snake head Velocity based on user input
	switch (next)
	{
	case Up:
		if (current != Down)
		{
			head.setVelocityX(0);
			head.setVelocityY(-1);
			current = next;
		}
		break;
	case Down:
		if (current != Up)
		{
			head.setVelocityX(0);
			head.setVelocityY(1);
			current = next;
		}
		break;
	case Left:
		if (current != Right)
		{
			head.setVelocityX(-1);
			head.setVelocityY(0);
			current = next;
		}
		break;
	case Right:
		if (current != Left)
		{
			head.setVelocityX(1);
			head.setVelocityY(0);
			current = next;
		}
		break;
	}

	// wait for next direction change
	next = None;
}// end turn


/******************************************************************************
move snake set distance
parameters: 
	distance	- in pixels to move snake
returns:
	void
******************************************************************************/
void Snake::move(float distance)
{
	// limit distance to full blocks only
	if (this->distance + distance > BLOCK_SIZE)
		distance = BLOCK_SIZE - this->distance;

	// set snake total distance moved
	this->distance += distance;

	Block* part = &head;
	while (part)
	{
		// move the block
		part->move(distance);

		// assign pointer to block after this one
		part = part->getAfter();
	}
}// end move


/******************************************************************************
the snake has moved one block size
parameters: 
	none
returns:
	bool	- true if moved full block size
******************************************************************************/
bool Snake::hasMoved()
{
	return distance >= BLOCK_SIZE;
}// end hasMoved


/******************************************************************************
reset snake distance and set snake direction and alignment
parameters: 
	none
returns:
	void
******************************************************************************/
void Snake::reset()
{
	// reset the snake distance to start another full block move
	distance = 0;

	Block* part = tail;
	while (part->getBefore())
	{
		// copy x velocity from block infront of this one
		part->setVelocityX(part->getBefore()->getVelocityX());

		// if block is moving horizontally now, then copy
		// the vertical coord of block infront for allignment
		if (part->getVelocityX())
			part->setY(part->getBefore()->getY());

		// copy y velocity from block infront of this one
		part->setVelocityY(part->getBefore()->getVelocityY());

		// if block is moving verticaly now, then copy
		// the vertical coord of block infront for allignment
		if (part->getVelocityY())
			part->setX(part->getBefore()->getX());

		part = part->getBefore();
	}// adjust velocities

}// end reset

/******************************************************************************
check if snake hits itself
parameters: 
	none
returns:
	bool	- true if snake hits itself
******************************************************************************/
bool Snake::hitSelf()
{
	bool collide = false;

	Block* part = head.getAfter();
	int skip = 3;
	while (part && !collide)
	{
		// skip first 3 blocks after the head
		if (skip)
			skip--;
		// check head w/ current part
		else
			collide = head.intersects(part);

		// move to the next part
		part = part->getAfter();
	}

	return collide;
}// end hitSelf

/******************************************************************************
check if snake hits a block
parameters: 
	block	- pointer to block to chec
	all		- false = check head ,true = check whole snake, default false
returns:
	bool	- true if snake hits a block
******************************************************************************/
bool Snake::hitBlock(Block* block, bool all)
{
	bool collide = head.intersects(block);

	// do we need to check the rest of the body
	if (all && !collide)
	{
		Block* part = head.getAfter();
		while (part && !collide)
		{
			// check block w/ current part
			collide = block->intersects(part);

			// move to the next part
			part = part->getAfter();
		}
	}

	return collide;
}// end hitBlock

/******************************************************************************
and block to snake when it eats food
parameters: 
	none
returns:
	void
******************************************************************************/
void Snake::grow()
{
	// save off the current tail
	tail->append(tail);

	tail = tail->getAfter();

	// move the tail one block in the opposite direction
	tail->setX(tail->getX() + tail->getVelocityX() * -1 * BLOCK_SIZE);
	tail->setY(tail->getY() + tail->getVelocityY() * -1 * BLOCK_SIZE);

	// add tail to snake and increase size
	size++;

}// end grow

/******************************************************************************
and block to snake when it eats food
parameters: 
	window		- handle to graphic window
returns:
	void
******************************************************************************/
void Snake::draw(OpenGL& window)
{
	Block* part = &head;
	while (part)
	{
		// draw the block
		part->draw(window);

		// assign pointer to block after this one
		part = part->getAfter();
	}
}