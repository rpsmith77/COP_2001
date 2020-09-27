/******************************************************************************
* File: snakemain.cpp
* Author: Ryan Smith
* Class: COP 2001 200205
* Purpose: main file for Snake game
******************************************************************************/

#include <iostream>

#include "opengl.h"		// graphics library

int main() {

	// create graphics window w/ 600 x 400 pixel dimenions and title
	OpenGL window; 
	window = OpenGL(600, 400, "Snake Game");

	//while (!window.isClosing()) {
	//	// clear window
	//	window.clearWindow();

	//	// draw box in window's buffer
	//	window.DrawSprite(100, 100, 10, 10, 0, 0, 255);

	//	// redraw the window
	//	window.paintWindow();
	//}

	//// pause program until user hits any key + enter
	//char pause;
	//std::cin >> pause;

	return 0;
} // end main