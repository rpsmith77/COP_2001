/******************************************************************************
* File: snakedefs.h
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: header file w/ program definitions for Snake Game
******************************************************************************/
#ifndef SNAKE_DEFS_H
#define SNAKE_DEFS_H

// games Frames per second (FPS)
const float FPS_RATE{ 1000 / 60.0f };

// game area boundries
const int GAME_WIDTH{ 400 };
const int GAME_HEIGHT{ 200 };

// game boundary and object sizes
const int MARGIN{ 10 };
const int BORDER_SIZE{ 2 };
const int BLOCK_SIZE{ 10 };

// head of the snake is index 0 in body array
const int SNAKE_HEAD{ 0 };

// how many pixels the snake should move in one full frame
const float SNAKE_VELOCITY{ 5 * BLOCK_SIZE };

// Window Properties
const int WINDOW_WIDTH{ GAME_WIDTH + 2 * MARGIN + 2 * BORDER_SIZE };
const int WINDOW_HEIGHT{ GAME_HEIGHT + 2 * MARGIN + 2 * BORDER_SIZE };
const char* WINDOW_TITLE = "Snake Game\0";

enum Border
{
	TopWall,
	BottomWall,
	LeftWall,
	RightWall,
};

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
	float x;			// left coord of top left corner
	float y;			// top coord of top left corner
	float width;		// width of block in pixels
	float height;		// height of block in pixels
	Color color;		// fill color for block
	float velocityX;	// speed of block horizontally in pixels/sec
	float velocityY;	// speed of block vertically in pixels/sec
};

const Color BORDER_COLOR{ Teal };
const Color SNAKE_COLOR{ Green };
const Color FOOD_COLOR{ Fuchsia };

// snake data structure that holds all of the blocks of the snake's body
// along with properties of the snake's current state
struct Snake
{
	// array of body blocks based size of screen in blocks
	Block body[(WINDOW_WIDTH / BLOCK_SIZE) * (WINDOW_HEIGHT / BLOCK_SIZE)];
	int size;				// how big the snake has grown (starts at 1)
	Direction current;		// current direction snake is traveling
	Direction next;			// next direction user has inputed
	float distance;			// distance snake has travled since last full block
};
#endif // !SNAKE_DEFS_H