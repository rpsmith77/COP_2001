/******************************************************************************
**   File: slopeInterceptMain.cpp
** Author: Ryan Smith
**  Class: COP 2001 202005
**Purpose: main application file that calculates and displays a line based on
**		   user input.
*******************************************************************************/

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>

#include "opengl.h"	// graphics library
#include "line.h"	// line object

//-----------------------------------------------------------------------------
// GLOBAL SPACE
//-----------------------------------------------------------------------------

//window dimensions
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const std::string WINDOW_TITLE = "Linear Graph";
// PI approximation
const double PI = 3.14159265;

//// point on linear graph
//struct Point
//{
//	float x;
//	float y;
//};
//
//// Line on a linear graph
//struct Line
//{
//	Point point1;
//	Point point2;
//	float slope;
//	float yIntercept;
//	float length;
//	float angle;
//};

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
		Line line = Line();

		// choose what proccess to go through depending on user's choice
		switch (mode)
		{
			// User enters 2 points
		case TWO_POINT:
			// user defined pints
			line = get2Point();

			// calculate line based off user input
			line.calculate();

			// text displays
			displayLine(line);
			display2Point(line);
			break;
			// User enters one point and the slope
		case POINT_SLOPE:
			// user defines one point and slope
			line = getPointSlope();

			// calculate line based off user input
			line.calculate();

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
		OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str());

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
	line	- line with 2 points
 ******************************************************************************/
Line get2Point()
{
	// get point 1 and 2
	Point one = getPoint();
	Point two = getPoint();
	Line line = Line(&one, &two);

	return line;
}// end get2Point

 /******************************************************************************
 create a line with point-slope form
 parameters:
	none
 returns:
	line	- line with 1 point and slope
 ******************************************************************************/
Line getPointSlope()
{
	Point one = getPoint();
	float slope = getSlope();
	Line line = Line(&one, slope);

	return line;
}// end getPointSlope

 /******************************************************************************
 get x y coords of a point from the user
 parameters:
	none
 returns:
	point	- a point with x y coords
 ******************************************************************************/
Point getPoint()
{
	Point point;
	//float input;
	// prompt for the point
	std::cout << "Enter a point for the line:\n"
			  << "Enter X and Y coordinates seperated by spaces: ";
	float x;
	float y;
	// user input
	std::cin >> x  >> y;

	point.setX(x);
	point.setY(y);

	return point;
}// end get point

 /******************************************************************************
 get slope from user for point-slope form
 parameters:
	none
 returns:
	slope	- slope of the line
 ******************************************************************************/
float getSlope()
{
	float slope;
	std::cout << "Enter the slope of the line: ";
	std::cin >> slope;
	return slope;
}// end getSlope

 /******************************************************************************
 Display information of the line
 parameters:
	line	- holds all relevant information of line
 returns:
	void
 ******************************************************************************/
void displayLine(Line line)
{
	std::cout << std::setprecision(3)
		<< "Line:\n"
		<< "\t\tPoint-1\t(" << line.getPoint1()->getX() << ", " << line.getPoint1()->getY() << ")\n"
		<< "\t\tPoint-2\t(" << line.getPoint2()->getX() << ", " << line.getPoint2()->getY() << ")\n"
		<< "\t\t  Slope = " << line.getSlope() << "\n"
		<< "\t       Y-Intcpt = " << line.getYIntercept() << "\n"
		<< "\t\t Length = " << line.getLength() << "\n"
		<< "\t\t  Angle = " << line.getAngle() << "\n";
}// end displayLine

 /******************************************************************************
 Display information of the line in two-point form
 parameters:
	line	- holds all relevant information of line
 returns:
	void
 ******************************************************************************/
void display2Point(Line line)
{
	std::cout << std::setprecision(3)
		<< "Two-point form:\n"
		<< "\t\t\t(" << line.getPoint2()->getY() << " - " << line.getPoint1()->getY() << ")\n"
		<< "\t\tm = ------------------------------------\n"
		<< "\t\t\t(" << line.getPoint2()->getX() << " - " << line.getPoint1()->getX() << ")\n";
}// end display2Point

 /******************************************************************************
 Display information of the line in point-slope form
 parameters:
	line	- holds all relevant information of line
 returns:
	void
 ******************************************************************************/
void displayPointSlope(Line line)
{
	std::cout << std::setprecision(3)
		<< "Point-slope form:\n"
		<< "\t\ty = " << line.getSlope() << "x + " << line.getYIntercept() << "\n";
}// end displayPointSlope

 /******************************************************************************
 Draw x y axis and line
 parameters:
	window	- display of graph
	line	- holds all relevant information of line
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
	float rotation{ line.getAngle() - 180 };
	// line color
	unsigned int lineColor{ 0xFF000000 }; // red
										  // line postion
	float linePostion[2] = { (WINDOW_WIDTH / 2) + line.getPoint1()->getX(), (WINDOW_WIDTH / 2) - line.getPoint1()->getY() };
	// line size
	float lineSize[2] = { width, line.getLength() };

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
	window	- display of graph
 returns:
	int		- value to close or keep window open
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