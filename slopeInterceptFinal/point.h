/******************************************************************************
**   File: point.h
** Author: Ryan Smith
**  Class: COP 2001 202005
**Purpose: header file for point object w/ linear x and y coordinates
*******************************************************************************/
#ifndef POINT_H
#define POINT_H

class Point
{
public:
	//-------------------------------------------------------------------------
	// constructors
	//-------------------------------------------------------------------------
	Point();					// default constructor
	Point(float x, float y);	// property construcor
	Point(Point* point);		// copy constructor

	//-------------------------------------------------------------------------
	// accessors (getters & setters)
	//-------------------------------------------------------------------------
	float getX();
	void  setX(float value);
	float getY();
	void  setY(float value);

	//-------------------------------------------------------------------------
	// member methods
	//-------------------------------------------------------------------------
	bool isEmpty();

private:

	float x;
	float y;

};

#endif // !POINT_H
