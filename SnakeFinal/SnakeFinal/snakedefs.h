/******************************************************************************
* File: snakedefs.h
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: header file w/ program definitions for Snake Game
******************************************************************************/
#ifndef SNAKE_DEFS_H
#define SNAKE_DEFS_H

#include <string>

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
const std::string WINDOW_TITLE = "Snake Game";

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

const Color BORDER_COLOR{ Teal };
const Color SNAKE_COLOR{ Green };
const Color FOOD_COLOR{ Fuchsia };

#endif // !SNAKE_DEFS_H