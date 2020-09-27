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
#include "block.h"		// game block object
#include "snake.h"		// snake object

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
bool CollisionChecks(Snake snake, Block borders[]);
Block NextFood(Snake snake);

int main()
{
	// initiate random number sequence
	srand(time(NULL));

	// create graphic window for drawing 
	OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str());

	// border walls
	Block borders[4];

	// the snake
	Snake snake = Snake(); // initialize w/ default constructor

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
		if (snake.getNext() == None)
		{
			snake.setNext(processInput(window));
		}

		// set game over if user decides to exit
		if (snake.getNext() == Exit)
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
	snake		- the snake class object
	food		- food block
returns:
	void
******************************************************************************/
void InitGameObjects(Block borders[], Snake& snake, Block& food)
{
	borders[TopWall] =	  Block(MARGIN,
						        MARGIN,
							    WINDOW_WIDTH - 2 * MARGIN,
							    BORDER_SIZE, 
							    BORDER_COLOR);

	borders[BottomWall] = Block(MARGIN,
								WINDOW_HEIGHT - MARGIN - BORDER_SIZE,
								WINDOW_WIDTH - 2 * MARGIN,
								BORDER_SIZE,
								BORDER_COLOR);

	borders[LeftWall] =   Block(MARGIN,
							    MARGIN,
							    BORDER_SIZE,
							    WINDOW_HEIGHT - 2 * MARGIN,
							    BORDER_COLOR);

	borders[RightWall] =  Block(WINDOW_WIDTH - MARGIN - BORDER_SIZE,
							    MARGIN,
							    BORDER_SIZE,
							    WINDOW_HEIGHT - 2 * MARGIN,
							    BORDER_COLOR);

	// set starting food location
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
  snake		- the snake class object
  borders	- array of border wall blocks
  food		- food block
  deltaTime	- accumulated frame time
returns:
  bool		- true if snake hit wall or self
******************************************************************************/
bool update(Snake& snake,Block borders[], Block& food, float deltaTime)
{
	bool collision = false;
	// skip updates until snake starts moving
	if (!snake.isMoving())
	{
		if (snake.getNext() == None)
			return collision;
		else
			// first turn
			snake.turn();
	}

	// turn

	float distance = SNAKE_VELOCITY / deltaTime;
	snake.move(distance);

	// has snake moved a full block
	if (snake.hasMoved())
	{
		snake.turn();

		snake.reset();

		// see if snake eats food
		if (snake.hitBlock(&food))
		{
			snake.grow();

			// new food block
			food = NextFood(snake);
		}
		else
			collision = CollisionChecks(snake, borders);	// game over

	}// end full block traversal

	return collision;
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
	snake.draw(window);
	
	// draw food block
	food.draw(window);

	// draw border walls
	borders[TopWall].draw(window);
	borders[BottomWall].draw(window);
	borders[LeftWall].draw(window);
	borders[RightWall].draw(window);



	// redraw window
	window.paintWindow();
} // end render

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
	if (snake.getCurrent() == Up && snake.hitBlock(&borders[TopWall]))
	{
		collide = true;
	}
	// if snake hits bottom wall
	else if (snake.getCurrent() == Down && snake.hitBlock(&borders[BottomWall]))
	{
		collide = true;
	}
	// if snake hits left wall
	else if (snake.getCurrent() == Left && snake.hitBlock(&borders[LeftWall]))
	{
		collide = true;
	}
	// if snake hits right wall
	else if (snake.getCurrent() == Right && snake.hitBlock(&borders[RightWall]))
	{
		collide = true;
	}
	// if snake hits self
	else
	{
		collide = snake.hitSelf();
	}

	return collide;
}


/******************************************************************************
check for collisions between the snake, the border, and itself
parameters: 
	snake	- snake structure
returns:
	Block	- location of next food
******************************************************************************/
Block NextFood(Snake snake)
{
	Block food = Block( 0, 0, BLOCK_SIZE, BLOCK_SIZE, FOOD_COLOR);

	bool placed{ false };
	while (!placed)
	{
		// get random x y coord within boundries
		int xCoord = rand() % (GAME_WIDTH - BLOCK_SIZE);
		int yCoord = rand() % (GAME_HEIGHT - BLOCK_SIZE);

		// move coords within visible screen
		xCoord += (MARGIN + BORDER_SIZE);
		yCoord += (MARGIN + BORDER_SIZE);

		// set coords
		food.setX(xCoord);
		food.setY(yCoord);

		placed = !snake.hitBlock(&food, true);


	}// while not placed

	return food;
}// end NextFood