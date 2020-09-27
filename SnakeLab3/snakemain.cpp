/******************************************************************************
* File: snakemain.cpp
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: main file for Snake game
******************************************************************************/
#include <iostream>		// console io
#include <stdlib.h>		// random numbers
#include <time.h>		// seed random numbers

#include "opengl.h"		// graphics library
#include "snakedefs.h"	// game definitions

//-----------------------------------------------------------------------------
// Global Space
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void InitGameObjects(Block borders[], Snake& snake, Block& food);
Direction processInput(OpenGL &window);
bool update(Snake& snake, Block borders[], Block& food, float deltaTime);
void render(OpenGL& window, Block borders[], Snake snake, Block food);
void DrawBlock(OpenGL& window, Block block);
bool Intersects(Block one, Block two);
bool CollisionChecks(Snake snake, Block borders[]);
bool IsMoving(Block block);
Block NextFood(Snake snake);

int main()
{
	// initiate random number sequence
	srand(time(NULL));

	// create graphic window for drawing
	OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// border walls
	Block borders[4];

	// the snake
	Snake snake;

	// food block
	Block food;

	InitGameObjects(borders, snake, food);

	// frame time variables
	//---------------------
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	// main game loop
	bool gameOver{ false };
	while (!gameOver && !window.isClosing())
	{
		// calculate delta time
		//---------------------
		float currentFrame = window.getTime();
		deltaTime += (currentFrame - lastFrame) * 1000;
		lastFrame = currentFrame;
		// get user input if not waiting to process input
		if (snake.next == None)
		{
			snake.next = processInput(window);
		}

		// set game over if user decides to exit
		if (snake.next == Exit)
		{
			gameOver = true;
		}

		// update game object at each sub-frame interval
		while (!gameOver && deltaTime >= FPS_RATE)
		{
			gameOver = update(snake, borders, food, deltaTime);
			deltaTime -= FPS_RATE;
		}

		// draw objects
		render(window, borders, snake, food);
		window.pollEvents();
	}

	std::cout << "Game Over!\nPress any key and enter to close:" << std::endl;
	char pause;
	std::cin >> pause;

	return 0; //echo %errorlevel%
}// end main

/******************************************************************************
intitialize game objects
parameters: 
	borders		- 4 boundray walls of the game
	snake		- the snake structure
	food		- food block
returns:
	void
******************************************************************************/
void InitGameObjects(Block borders[], Snake& snake, Block& food)
{
	borders[TopWall] =	  { MARGIN,
						    MARGIN,
							WINDOW_WIDTH - 2 * MARGIN,
							BORDER_SIZE, 
							BORDER_COLOR,
							0,0 };

	borders[BottomWall] = { MARGIN,
							WINDOW_HEIGHT - MARGIN - BORDER_SIZE,
							WINDOW_WIDTH - 2 * MARGIN,
							BORDER_SIZE,
							BORDER_COLOR,
							0,0 };

	borders[LeftWall] =   { MARGIN,
							MARGIN,
							BORDER_SIZE,
							WINDOW_HEIGHT - 2 * MARGIN,
							BORDER_COLOR,
							0,0 };

	borders[RightWall] =  { WINDOW_WIDTH - MARGIN - BORDER_SIZE,
							MARGIN,
							BORDER_SIZE,
							WINDOW_HEIGHT - 2 * MARGIN,
							BORDER_COLOR,
							0,0 };

	// Starting location of snake's head
	snake.body[SNAKE_HEAD] = {	WINDOW_WIDTH / 2 + BLOCK_SIZE / 2,
								WINDOW_HEIGHT / 2 + BLOCK_SIZE / 2,
								BLOCK_SIZE,
								BLOCK_SIZE,
								SNAKE_COLOR,
								0, 0 };
	snake.size = 1;
	snake.current = None;
	snake.next = None;
	snake.distance = 0;

	food = NextFood(snake);
}// end InitGameObjects

 /******************************************************************************
 returns direction to move block from user input
 parameters:
	window		- display of snake game
 returns:
	dir			- direction of to move block
 ******************************************************************************/
Direction processInput(OpenGL &window)
{
	Direction dir{ None };

	// read user input
	GL_KEY key = window.GetKey();

	switch (key)
	{
		// exit game
	case GL_KEY::KEY_ESC:
	case GL_KEY::KEY_X:
		dir = Direction::Exit;
		break;
		// up
	case GL_KEY::KEY_W:
	case GL_KEY::KEY_UP_ARROW:
		dir = Direction::Up;
		break;
		// left
	case GL_KEY::KEY_A:
	case GL_KEY::KEY_LEFT_ARROW:
		dir = Direction::Left;
		break;
		// down
	case GL_KEY::KEY_S:
	case GL_KEY::KEY_DOWN_ARROW:
		dir = Direction::Down;
		break;
		// right
	case GL_KEY::KEY_D:
	case GL_KEY::KEY_RIGHT_ARROW:
		dir = Direction::Right;
		break;
	} // end swith key

	return dir;
} // end processInput

/******************************************************************************
update game objects
 parameters:
  snake		- the snake structure
  borders	- array of border wall blocks
  food		- food block
  deltaTime	- accumulated frame time
returns:
  bool		- true if snake hit wall or self
******************************************************************************/
bool update(Snake& snake,Block borders[], Block& food, float deltaTime)
{
	// skip updates until snake starts moving
	if (snake.next == None && !IsMoving(snake.body[SNAKE_HEAD]))
	{
		return false;
	}

	// process any user direction change
	if (snake.next != None)
	{
		// adjust snake head velocity based on user input
		switch (snake.next)
		{
		case Up:
			if (snake.current != Down)
			{
				snake.body[SNAKE_HEAD].velocityX = 0;
				snake.body[SNAKE_HEAD].velocityY = -1;
				snake.current = snake.next;
			}
			break;
		case Down:
			if (snake.current != Up)
			{
				snake.body[SNAKE_HEAD].velocityX = 0;
				snake.body[SNAKE_HEAD].velocityY = 1;
				snake.current = snake.next;
			}
			break;
		case Left:
			if (snake.current != Right)
			{
				snake.body[SNAKE_HEAD].velocityX = -1;
				snake.body[SNAKE_HEAD].velocityY = 0;
				snake.current = snake.next;
			}
			break;
		case Right:
			if (snake.current != Left)
			{
				snake.body[SNAKE_HEAD].velocityX = 1;
				snake.body[SNAKE_HEAD].velocityY = 0;
				snake.current = snake.next;
			}
			break;
		}

		// wait for next direction change
		snake.next = None;
	}// end direction change

	float distance = SNAKE_VELOCITY / deltaTime;
	snake.distance += distance;

	// has snake moved a full block
	if (snake.distance < BLOCK_SIZE)
	{
		// if not move each block a fractional amount
		for (int i = 0; i < snake.size; i++)
		{
			snake.body[i].x += snake.body[i].velocityX * distance;
			snake.body[i].y += snake.body[i].velocityY * distance;
		}
	}
	else // the snake has moved a full block
	{
		// reset the snake distance to start another full block move
		snake.distance = 0;

		// from tail to head, make the velocity the same as the block infront
		// to make the the blocks follow eachother
		for (int i = snake.size - 1; i > 0; i--)
		{
			// copy x velocity from block infront of this one
			snake.body[i].velocityX = snake.body[i - 1].velocityX;

			// if block is moving horizontally now, then copy
			// the vertical coord of block infront for allignment
			if (snake.body[i].velocityX)
				snake.body[i].y = snake.body[i - 1].y;

			// copy y velocity from block infront of this one
			snake.body[i].velocityY = snake.body[i - 1].velocityY;

			// if block is moving verticaly now, then copy
			// the vertical coord of block infront for allignment
			if (snake.body[i].velocityY)
				snake.body[i].x = snake.body[i - 1].x;
			

		}// end loop tail to head

		// see if snake eats food
		if (Intersects(snake.body[SNAKE_HEAD], food))
		{
			// save off the current tail location
			Block tail = snake.body[snake.size - 1];

			// move the tail one block in the opposite direction
			tail.x += tail.velocityX * -1 * BLOCK_SIZE;
			tail.y += tail.velocityY * -1 * BLOCK_SIZE;

			// add tail to snake and increase size
			snake.body[snake.size] = tail;
			snake.size++;

			// new food block
			food = NextFood(snake);
		}
		else if (CollisionChecks(snake, borders))
			return true;	// game over

	}// end full block traversal

	return false;
}// end update


/******************************************************************************
draws all game objects
parameters: 
	window		- display for snake game
	borders		- 4 boundray walls of the game
	snake		- the snake structure
	food		- food block
returns:
	void
******************************************************************************/
void render(OpenGL &window, Block borders[], Snake snake, Block food)
{
	// set background color
	Color background = White;

	// clear window
	window.clearWindow(reinterpret_cast<const unsigned char*>(&background));

	// draw snake
	for (int i = 0; i < snake.size; i++)
	{
		DrawBlock(window, snake.body[i]);
	}
	

	// draw food block
	DrawBlock(window, food);

	// draw border walls
	DrawBlock(window, borders[TopWall]);
	DrawBlock(window, borders[BottomWall]);
	DrawBlock(window, borders[LeftWall]);
	DrawBlock(window, borders[RightWall]);



	// redraw window
	window.paintWindow();
} // end render

/******************************************************************************
draw a block structure
parameters: 
	window	- display for snake game
	block	- a block sturcture
returns:
	void
******************************************************************************/
void DrawBlock(OpenGL& window, Block block)
{
	float postion[2]{ block.x, block.y };		// top left corner location
	float size[2]{ block.width, block.height }; // width and height
	window.DrawSprite(postion, size, reinterpret_cast<unsigned char*>(&block.color));
}// end drawBlock

/******************************************************************************
determine if two blocks intersect
parameters: 
	one		- block one
	two		- block two
returns:
	bool	- true if intersects
******************************************************************************/
bool Intersects(Block one, Block two)
{
	return !(int(two.x) > int(one.x + one.width) ||
			 int(two.x + two.width) < int(one.x) ||
			 int(two.y) > one.y + int(one.height) ||
			 int(two.y + two.height) < int(one.y));

}

/******************************************************************************
check for collisions between the snake, the border, and itself
parameters: 
	snake	- snake structure
	borders	- walls
returns:
	bool	- true if intersects
******************************************************************************/
bool CollisionChecks(Snake snake, Block borders[])
{
	bool collide{ false };

	// if snake hits top wall
	if (snake.current == Up && Intersects(snake.body[SNAKE_HEAD], borders[TopWall]))
	{
		collide = true;
	}
	// if snake hits bottom wall
	else if (snake.current == Down && Intersects(snake.body[SNAKE_HEAD], borders[BottomWall]))
	{
		collide = true;
	}
	// if snake hits left wall
	else if (snake.current == Left && Intersects(snake.body[SNAKE_HEAD], borders[LeftWall]))
	{
		collide = true;
	}
	// if snake hits right wall
	else if (snake.current == Right && Intersects(snake.body[SNAKE_HEAD], borders[RightWall]))
	{
		collide = true;
	}
	// if snake hits self
	else
	{
		for (int i = 3; i < snake.size; i++)
		{
			if (!collide)
				collide = Intersects(snake.body[SNAKE_HEAD], snake.body[i]);
		}
	}

	return collide;
}

/******************************************************************************
detrimine if block has either x or y velocity
parameters: 
	block	- a block sturcture
returns:
	bool	- true if block moving
******************************************************************************/
bool IsMoving(Block block)
{
	return int(block.velocityX) || int(block.velocityY);
}// end IsMoving

/******************************************************************************
check for collisions between the snake, the border, and itself
parameters: 
	snake	- snake structure
returns:
	Block	- location of next food
******************************************************************************/
Block NextFood(Snake snake)
{
	Block food = { 0, 0, BLOCK_SIZE, BLOCK_SIZE, FOOD_COLOR, 0, 0 };

	bool placed{ false };
	while (!placed)
	{
		// get random x y coord within boundries
		food.x = rand() % (GAME_WIDTH - BLOCK_SIZE);
		food.y = rand() % (GAME_HEIGHT - BLOCK_SIZE);

		// move coords within visible screen
		food.x += (MARGIN + BORDER_SIZE);
		food.y += (MARGIN + BORDER_SIZE);

		placed = true;		// assume we will find open spot

		// check if snake occupies location
		for (int i = 0; i < snake.size; i++)
		{
			if (Intersects(food, snake.body[i]))
			{
				placed = false;
				break;		// exit snake loop
			}
		}// snake loop

	}// while not placed

	return food;
}// end NextFood