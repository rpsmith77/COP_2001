/******************************************************************************
* File: snakemain.cpp
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: main file for Snake game
******************************************************************************/

#include <iostream>
#include <string>

#include "opengl.h"		// graphics library


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
// Window Properties
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 400;
const char* WINDOW_TITLE = "Snake Game\0";
// Block Properties
const int BLOCK_WIDTH = 10;
const int BLOCK_HEIGHT = 10;

// color hex codes
enum Color
{
	White = 0xFFFFFF00,
	Silver = 0xC0C0C000,
	Gray = 0x80808000,
	Black = 0x00000000,
	Red = 0xFF000000,
	Maroon = 0x80000000,
	Yellow = 0xFFFF0000,
	Olive = 0x80800000,
	Lime = 0x00FF0000,
	Green = 0x00800000,
	Aqua = 0x00FFFF00,
	Teal = 0x00808000,
	Blue = 0x0000FF00,
	Navy = 0x00008000,
	Fuchsia = 0xFF00FF00,
	Purple = 0x80008000
};

// direction
enum Direction
{
	Exit = -1,
	None,
	Up,
	Down,
	Left,
	Right
};

struct Block
{
	// x coordinate
	float x;
	// y coordinate
	float y;
	// dimensions
	float width;
	float height;
	// color
	Color color = Blue;
};

Direction processInput(OpenGL &window);
void update(Block &block, Direction dir);
void render(OpenGL &window, Block block);


int main()
{

	// create graphics window w/ 600 x 400 pixel dimenions and title
	OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// create Block
	Block block;
	//----------------------------------------
	// intital block properties
	//----------------------------------------
	// x y coords in center of window
	block.x = WINDOW_WIDTH / 2 - BLOCK_WIDTH / 2;
	block.y = WINDOW_HEIGHT / 2 - BLOCK_HEIGHT / 2;
	// 10 x 10 pixel dimension
	block.width = BLOCK_WIDTH;
	block.height = BLOCK_HEIGHT;
	// color
	block.color = White;


	bool gameOver{ false };

	while (!window.isClosing() && !gameOver)
	{
		Direction dir = processInput(window);
		if (dir == Exit)
		{
			gameOver = true;
		}
		update(block, dir);
		render(window, block);
		window.pollEvents();
	}


	// pause program until user hits any key + enter
	char pause;
	std::cin >> pause;

	return 0;
} // end main

Direction processInput(OpenGL &window)
{
	Direction dir{ None };

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

void update(Block &block, Direction dir)
{
	switch (dir)
	{
	// move one block length up
	case Up:
		block.y -= block.height;
		break;
	// move one block length down
	case Down:
		block.y += block.height;
		break;
	// move one block length left
	case Left:
		block.x -= block.width;
		break;
	// move one block length right
	case Right:
		block.x += block.width;
		break;
	
	}
} // end update

void render(OpenGL &window, Block block)
{
	// set background color
	Color background = Teal;

	// clear window
	window.clearWindow(reinterpret_cast<const unsigned char*>(&background));

	// local block properties
	float blockPosition[2]{ block.x, block.y };
	float blockSize[2]{ block.width, block.height };
	unsigned char* blockColor = reinterpret_cast<unsigned char*>(&block.color);
	// draw block in window buffer
	window.DrawSprite(blockPosition, blockSize, blockColor);

	// redraw window
	window.paintWindow();
} // end render

