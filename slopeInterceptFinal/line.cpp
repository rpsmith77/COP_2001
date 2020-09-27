/******************************************************************************
**   File: line.cpp
** Author: Ryan Smith
**  Class: COP 2001 202005
**Purpose: implementation file for line object w/ two point objects, slope,
**		   y-intercept, length, and angle.
*******************************************************************************/
#include "line.h"
#include <math.h>
#include <iomanip>

//-------------------------------------------------------------------------
// constructors
//-------------------------------------------------------------------------
/**************************************************************************
default constructor
**************************************************************************/
Line::Line()
{
	point1 = Point();
	point2 = Point();
	slope = 0.0f;
	yIntercept = 0.0f;
	length = 0.0f;
	angle = 0.0f;
}

/**************************************************************************
property constructors
**************************************************************************/
Line::Line(Point* one, Point* two)
{
	point1 = one;
	point2 = two;
}

Line::Line(Point* one, float slope)
{
	point1 = one;
	point2 = Point();
	this->slope = slope;
}
//-------------------------------------------------------------------------
// accessors (getters & setters)
//-------------------------------------------------------------------------
Point* Line::getPoint1() { return &point1; }
Point* Line::getPoint2() { return &point2; }
float  Line::getSlope() { return slope; }
void   Line::setSlope(float value) { slope = value; }
float  Line::getYIntercept() { return yIntercept; }
void   Line::setYIntercept(float value) { yIntercept = value; }
float  Line::getLength() { return	length; }
void   Line::setLength(float value) { length = value; }
float  Line::getAngle() { return angle; }
void   Line::setAngle(float value) { angle = value; }

//-------------------------------------------------------------------------
// member methods
//-------------------------------------------------------------------------
/******************************************************************************
calculate slope from 2 points
parameters:
	line	- holds all relevant information of line
returns:
	void
******************************************************************************/
void Line::slopeFrom2Point()
{
	/************************************
	Formula:	slope = (y2-y1) / (x2-x1)
	************************************/
	slope = (point2.getY() - point1.getY()) / (point2.getX() - point1.getX());
}// end slopeFrom2Point

 /******************************************************************************
 calculate the y intercept
 parameters:
	none
 returns:
	void
 ******************************************************************************/
void Line::slopeIntercept()
{
	/**********************************
	Formula:	intercept = y -(slope)x
	**********************************/
	yIntercept = point1.getY() - (getSlope() * point1.getX());
}// end slopeIntercept

 /******************************************************************************
 calculate the length of the line
 parameters:
	none
 returns:
	void
 ******************************************************************************/
void Line::lineLength()
{
	/*******************************************
	Formula:	L = sqrt( (x2-x1)^2 + (y2-y1)^2)
	*******************************************/
	length = sqrt(powf(point2.getX() - point1.getX(), 2) + powf(point2.getY() - point1.getY(), 2));
}// end getLineLength

 /******************************************************************************
 calculate the angle of the line
 parameters:
	none
 returns:
	none
 ******************************************************************************/
void Line::lineAngle()
{
	double PI = 3.14159265; // aproximation for pi
	/******************************************************
	Formula:	Theta = (90 - arctan(slope) * 180/PI) % 360
	******************************************************/
	angle = std::fmod(90.0 - float((std::atan(slope) * 180.0 / PI)), 360);
}// end lineAngle

 /******************************************************************************
 perform all calculations needed for 2 point form and point slope form
 parameters:
	none
 returns:
	none
 ******************************************************************************/
void Line::calculate()
{
	// if point 2 is empty then its point slope
	if (point2.isEmpty())
	{
		// y intercept
		slopeIntercept();

		// set point 2 to y intercept
		point2 = Point(0, getYIntercept());

		// line length
		lineLength();

		// line angle;
		lineAngle();
	}
	// 2 point form
	else
	{
		// slope
		slopeFrom2Point();

		// y intercept
		slopeIntercept();

		// line length
		lineLength();

		// line angle;
		lineAngle();
	}
}// end calculate