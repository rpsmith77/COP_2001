/******************************************************************************
* File: block.h
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: Implementation file w/ program definitions for block class that represents
		   a rectangle game object w/ position, size, and velocity
******************************************************************************/
#include "block.h"

//-----------------------------------------------------------------------------
// consturctors
//-----------------------------------------------------------------------------
/******************************************************************************
default constructor
******************************************************************************/
Block::Block()
{
	x = 0.0f;			
	y = 0.0f;			
	width = 0;			
	height = 0;		
	color = Black;		
	velocityX = 0.0f;	
	velocityY = 0.0f;
	before = nullptr;
	after = nullptr;
}

/******************************************************************************
property constructor
******************************************************************************/
Block::Block(float x, float y, float width, float height, Color color,
			 float velocityX, float velocityY, Block* before, Block* after)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	this->before = before;
	this->after = after;
}

/******************************************************************************
copy constructor
******************************************************************************/
Block::Block(Block* block)
{
	x = block->x;
	y = block->y;
	width = block->width;
	height = block->height;
	color = block->color;
	velocityX = block->velocityX;
	velocityY = block->velocityY;
	before = block->before;
	after = block->after;
}


//-----------------------------------------------------------------------------
// accessors (getters and setters)
//-----------------------------------------------------------------------------
float  Block::getX() { return x; }
void   Block::setX(float value) { x = value; }
float  Block::getY() { return y; }
void   Block::setY(float value) { y = value; }
int    Block::getWidth() { return width; }
void   Block::setWidth(int value) { width = value; }
int    Block::getHeight() { return height; }
void   Block::setHeight(int value) { height = value; }
Color  Block::getColor() { return color; }
void   Block::setColor(Color value) { color = value; }
float  Block::getVelocityX() { return velocityX; }
void   Block::setVelocityX(float value) { velocityX = value; }
float  Block::getVelocityY() { return velocityY; }
void   Block::setVelocityY(float value) { velocityY = value; }
Block* Block::getBefore() { return before; }
void   Block::setBefore(Block* ptrBlock) { before = ptrBlock; }
Block* Block::getAfter() { return after; }
void   Block::setAfter(Block* ptrBlock) { after = ptrBlock; }


//----------------------------------------------------------------------------
// member methods
//----------------------------------------------------------------------------

/******************************************************************************
draw this block object
parameters: 
	window	- display for snake game
returns:
	void
******************************************************************************/
void Block::draw(OpenGL& window)
{
	float postion[2]{ x, y };		// top left corner location
	float size[2]{ width, height }; // width and height
	window.DrawSprite(postion, size, reinterpret_cast<unsigned char*>(&color));
}

/******************************************************************************
determine if other block intersects this block
parameters: 
	other	- block to see intersects
returns:
	bool	- true if intersects
******************************************************************************/
bool Block::intersects(Block* other)
{
	return !(int(other->x) > int(this->x + this->width) ||
			 int(other->x + other->width) < int(this->x) ||
			 int(other->y) > this->y + int(this->height) ||
			 int(other->y + other->height) < int(this->y));
}

/******************************************************************************
detrimine if block has either x or y velocity
parameters: 
	none
returns:
	bool	- true if block moving
******************************************************************************/
bool Block::isMoving()
{
	return int(velocityX) || int(velocityY);
}// end isMoving

/******************************************************************************
move block set distance and velocities
parameters: 
	distance	- in pixels to move block
returns:
	void
******************************************************************************/
void Block::move(float distance)
{
	x += velocityX * distance;
	y += velocityY * distance;
}// end move

/******************************************************************************
link new block to the after pointer of this block
parameters: 
	other	- append copy of
returns:
	void
******************************************************************************/
void Block::append(Block* other)
{
	// create new block as copy of other
	Block* newTail = new Block(other);

	// attach new block behind this one
	after = newTail;

	// make new blocks forward pointer point to this one
	newTail->before = this;
}
