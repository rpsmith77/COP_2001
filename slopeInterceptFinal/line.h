/******************************************************************************
**   File: line.h
** Author: Ryan Smith
**  Class: COP 2001 202005
**Purpose: header file for line object w/ two point objects, slope, y-intercept,
**		   length, and angle.
*******************************************************************************/
#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
public:
	//-------------------------------------------------------------------------
	// constructors
	//-------------------------------------------------------------------------
	Line();			// default
	Line(Point* one, Point* two);
	Line(Point* one, float slope);
	//-------------------------------------------------------------------------
	// accessors (getters & setters)
	//-------------------------------------------------------------------------
	Point* getPoint1();
	Point* getPoint2();
	float  getSlope();
	void   setSlope(float value);
	float  getYIntercept();
	void   setYIntercept(float value);
	float  getLength();
	void   setLength(float value);
	float  getAngle();
	void   setAngle(float value);
	//-------------------------------------------------------------------------
	// member methods
	//-------------------------------------------------------------------------
	void slopeFrom2Point();
	void slopeIntercept();
	void lineLength();
	void lineAngle();
	void calculate();

private:

	Point point1;
	Point point2;
	float slope;
	float yIntercept;
	float length;
	float angle;

};


#endif // !LINE_H
