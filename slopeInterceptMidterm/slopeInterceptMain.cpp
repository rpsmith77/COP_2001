/******************************************************************************
**   File: slopeInterceptMain.cpp
** Author: Ryan Smith
**  Class: COP 2001 202005
**Purpose: main application file that calculates and displays a line based on
**		   user input.
*******************************************************************************/

#include <iostream>
#include <math.h>
#include <iomanip>

#include "opengl.h"	// graphics library

//-----------------------------------------------------------------------------
// GLOBAL SPACE
//-----------------------------------------------------------------------------

//window dimensions
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const char* WINDOW_TITLE = "Linear Graph\0";
// PI approximation
const double PI = 3.14159265;

// point on linear graph
struct Point
{
	float x;
	float y;
};

// Line on a linear graph
struct Line
{
	Point point1;
	Point point2;
	float slope;
	float yIntercept;
	float length;
	float angle;
};

// user options
enum Mode
{
	TWO_POINT = 1,
	POINT_SLOPE,
	EXIT
};

//-----------------------------------------------
// Function Prototypes
//-----------------------------------------------
Mode getProblem();
Line get2Point();
Line getPointSlope();
Point getPoint();
float getSlope();
float getSlopeFrom2Point(Line line);
float getYIntercept(Line line);
float getLineLength(Line line);
float getLineAngle(Line line);
void displayLine(Line line);
void display2Point(Line line);
void displayPointSlope(Line line);
void drawLine(OpenGL &window, Line line);
int exitGraph(OpenGL &window);

int main()
{
	// ask user to choose mode until user exits
	while (true)
	{
		// different options for user
		Mode mode;

		// get which mode user wants to use
		mode = getProblem();

		// create line for the graph
		Line line;

		// choose what proccess to go through depending on user's choice
		switch (mode)
		{
		// User enters 2 points
		case TWO_POINT:
			// user defined pints
			line = get2Point();

			// calculate slope
			line.slope = getSlopeFrom2Point(line);

			// calculate y intercept
			line.yIntercept = getYIntercept(line);

			// calculate line length
			line.length = getLineLength(line);

			// calculate line angle
			line.angle = getLineAngle(line);

			// text displays
			displayLine(line);
			display2Point(line);
			break;
		// User enters one point and the slope
		case POINT_SLOPE:
			// user defines one point and slope
			line = getPointSlope();

			// calculate y intercept
			line.yIntercept = getYIntercept(line);

			// set point2 to y intercept
			line.point2.y = line.yIntercept;
			line.point2.x = 0;

			// calculate line length
			line.length = getLineLength(line);

			// calculate line angle
			line.angle = getLineAngle(line);
			
			// text displays
			displayLine(line);
			displayPointSlope(line);
			break;
		// terminate program
		case EXIT:
			return 0;
			break;
		}// end swith (mode)

		// create window to display graph
		OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

		bool exitDisplay{ false };
		// loop until exited
		while (!window.isClosing() && !exitDisplay)
		{
			// draw axis and line
			drawLine(window, line);
			// read user input to exit graph
			int dir = exitGraph(window);
			if (dir == 1)
			{
				exitDisplay = true;
			}
			
			window.pollEvents();
		}// end graph loop

	}
}// end main

/******************************************************************************
Prompt user for which form they want to use or to exit
parameters: 
	none
returns:
	which form of data entry or exit
******************************************************************************/
Mode getProblem()
{
	// prompt
	std::cout << "Select the form you would like to convert to slope-intercept form:\n"
			  << "\t1) Two-point form (you know two points on the line)\n"
			  << "\t2) Point-slope form (you know the slope and one point of the line)\n"
			  << "\t3) Exit\n";

	Mode mode;
	int input{ 0 };
	std::cin >> input;
	switch (input)
	{
	case 1:
		mode = TWO_POINT;
		break;
	case 2:
		mode = POINT_SLOPE;
		break;
	case 3:
		mode = EXIT;
		break;
	}

	return mode;
}// end getProblem

/******************************************************************************
create a line with two-point form
parameters: 
	none
returns:
	line with 2 points
******************************************************************************/
Line get2Point()
{
	Line line;

	// get point 1 and 2
	line.point1 = getPoint();
	line.point2 = getPoint();

	return line;
}// end get2Point

/******************************************************************************
create a line with point-slope form
parameters: 
	none
returns:
	line with 1 point and slope
******************************************************************************/
Line getPointSlope()
{
	Line line;

	// prompt for point
	line.point1 = getPoint();

	// prompt for slope
	line.slope = getSlope();

	return line;
}// end getPointSlope

/******************************************************************************
get x y coords of a point from the user
parameters: 
	none
returns:
	point - a point with x y coords
******************************************************************************/
Point getPoint()
{
	Point point;
	//float input;
	// prompt for the point
	std::cout << "Enter a point for the line:\n"
			  << "Enter X and Y coordinates seperated by spaces: ";
	// user input
	std::cin >> point.x >> point.y;

	return point;
}// end get point

/******************************************************************************
get slope from user for point-slope form
parameters: 
	none
returns:
	slope - slope of the line
******************************************************************************/
float getSlope()
{
	float slope;
	std::cout << "Enter the slope of the line: ";
	std::cin >> slope;
	return slope;
}// end getSlope

/******************************************************************************
calculate slope from 2 points
parameters: 
	line - holds all relevant information of line
returns:
	slope of line from 2 points
******************************************************************************/
float getSlopeFrom2Point(Line line)
{
	 /* Formula:
	 slope = (y2-y1) / (x2-x1)
	 */
	return (line.point2.y - line.point1.y) / (line.point2.x - line.point1.x);
}// end getSlopeFrom2Point

/******************************************************************************
calculate the y intercept
parameters: 
	line - holds all relevant information of line
returns:
	x coordinate where y = 0
******************************************************************************/
float getYIntercept(Line line)
{
	/* Formula:
	intercept = y -(slope)x
	*/
	return line.point1.y - (line.slope * line.point1.x);
}// end getYIntercept

/******************************************************************************
calculate the length of the line
parameters: 
	line - holds all relevant information of line
returns:
	float value of length of line
******************************************************************************/
float getLineLength(Line line)
{
	/* Formula for length of line
	L = sqrt( (x2-x1)^2 + (y2-y1)^)
	*/
	return sqrt(powf(line.point2.x - line.point1.x, 2) + powf(line.point2.y - line.point1.y, 2));
}// end getLineLength

/******************************************************************************
calculate the angle of the line
parameters: 
	line - holds all relevant information of line
returns:
	float value of the angle of the line
******************************************************************************/
float getLineAngle(Line line)
{
	/* Formula for line angle:
	Theta = (90 - arctan(slope) * 180/PI) % 360
	*/
	return std::fmod(90.0 - float((std::atan(line.slope) * 180.0 / PI)), 360);
}// end getLineAngle

/******************************************************************************
Display information of the line
parameters: 
	line - holds all relevant information of line
returns:
	void
******************************************************************************/
void displayLine(Line line)
{
	std::cout << std::setprecision(3) 
			  << "Line:\n"
			  << "\t\tPoint-1\t(" << line.point1.x << ", " << line.point1.y << ")\n"
			  << "\t\tPoint-2\t(" << line.point2.x << ", " << line.point2.y << ")\n"
			  << "\t\t  Slope = " << line.slope << "\n"
			  << "\t       Y-Intcpt = " << line.yIntercept << "\n"
			  << "\t\t Length = " << line.length << "\n"
			  << "\t\t  Angle = " << line.angle << "\n";
}// end displayLine

/******************************************************************************
Display information of the line in two-point form
parameters: 
	line - holds all relevant information of line
returns:
	void
******************************************************************************/
void display2Point(Line line)
{
	std::cout << std::setprecision(3) 
			  << "Two-point form:\n"
			  << "\t\t\t(" << line.point2.y << " - " << line.point1.y << ")\n"
			  << "\t\tm = ------------------------------------\n"
			  << "\t\t\t(" << line.point2.x << " - " << line.point1.x << ")\n";
}// end display2Point

/******************************************************************************
Display information of the line in point-slope form
parameters: 
	line - holds all relevant information of line
returns:
	void
******************************************************************************/
void displayPointSlope(Line line)
{
	std::cout << std::setprecision(3)
			  << "Point-slope form:\n"
			  << "\t\ty = " << line.slope << "x + " << line.yIntercept << "\n";
}// end displayPointSlope

/******************************************************************************
Draw x y axis and line
parameters: 
	window - display of graph
	line - holds all relevant information of line
returns:
	void
******************************************************************************/
void drawLine(OpenGL &window, Line line)
{
	//-------------------------------------------
	// Axis Properties
	//-------------------------------------------
	// x axis properties
	float xAxisPostion[2] = { 0, WINDOW_HEIGHT / 2 };
	float xAxisSize[2] = { WINDOW_WIDTH, 1 };
	// y axis properties
	float yAxisPostion[2] = { WINDOW_WIDTH / 2, 0 };
	float yAxisSize[2] = { 1, WINDOW_HEIGHT };
	// axis color
	unsigned int axisColor{ 0x00000000 }; // black

	//-------------------------------------------
	// Line properties
	//-------------------------------------------
	float width{ 2 };
	// Line starts pointing down so this fixes the lines orientation
	float rotation{ line.angle - 180 };
	// line color
	unsigned int lineColor{ 0xFF000000 }; // red
	// line postion
	float linePostion[2] = { (WINDOW_WIDTH / 2) + line.point1.x, (WINDOW_WIDTH / 2) - line.point1.y };
	// line size
	float lineSize[2] = { width, line.length };

	//background color
	unsigned int backgroundColor{ 0xFFFFFF00 }; // white

	window.clearWindow(reinterpret_cast<unsigned char*>(&backgroundColor));

	// draw x axis
	window.DrawSprite(xAxisPostion, xAxisSize,
		reinterpret_cast<unsigned char*>(&axisColor));
	// draw y axis
	window.DrawSprite(yAxisPostion, yAxisSize,
		reinterpret_cast<unsigned char*>(&axisColor));

	// draw line
	window.DrawSprite(linePostion, lineSize,
		reinterpret_cast<unsigned char*>(&lineColor),
		rotation,
		false); // roatates around point instead of center

	// redraw window
	window.paintWindow();
}// end drawLine

/******************************************************************************
Close graph window
parameters: 
	window - display of graph
returns:
	int value to close or keep window open
******************************************************************************/
int exitGraph(OpenGL &window)
{
	GL_KEY key = window.GetKey();

	if (key == KEY_ESC || key == KEY_X)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}// end exitGraph