/******************************************************************************
* File: block.h
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: header file w/ program definitions for block class that represents
		   a rectangle game object w/ position, size, and velocity
******************************************************************************/

#ifndef BLOCK_H
#define BLOCK_H

#include "snakedefs.h"
#include "opengl.h"

class Block
{
public:
	//----------------------------------------------------------------------------
	// consturctors
	//----------------------------------------------------------------------------
	Block();	// default
	Block(float x, float y, float width, float height, Color color, 
		  float velocityX = 0, float velocityY = 0,
		  Block* before = nullptr, Block* after = nullptr);
	Block(Block* block);	// copy constructor


	//----------------------------------------------------------------------------
	// accessors (getters and setters)
	//----------------------------------------------------------------------------
	float  getX();
	void   setX(float value);
	float  getY();
	void   setY(float value);
	int    getWidth();
	void   setWidth(int value);
	int    getHeight();
	void   setHeight(int value);
	Color  getColor();
	void   setColor(Color value);
	float  getVelocityX();
	void   setVelocityX(float value);
	float  getVelocityY();
	void   setVelocityY(float value);
	Block* getBefore();
	void   setBefore(Block* ptrBlock);
	Block* getAfter();
	void   setAfter(Block* ptrBlock);


	//----------------------------------------------------------------------------
	// member methods
	//----------------------------------------------------------------------------
	void draw(OpenGL& window);
	bool intersects(Block* other);
	bool isMoving();
	void move(float distance);
	void append(Block* other);

private:
	float x;			// left coord of top left corner
	float y;			// top coord of top left corner
	float width;		// width of block in pixels
	float height;		// height of block in pixels
	Color color;		// fill color for block
	float velocityX;	// speed of block horizontally in pixels/sec
	float velocityY;	// speed of block vertically in pixels/sec
	Block* before;
	Block* after;
};


#endif // !BLOCK_H
