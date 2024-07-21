/***********************************************************
 *  Paint.h                                                *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright � 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#pragma once

#include <fstream>
#include <sstream>
#include <conio.h>
#include <ctime>
#include "Rectangle.h"
#include "Circle.h"
#include 

class Factory {
public:
	virtual Shape* CreateShape() = 0;
};

class RobustShapeFactory : public Factory {
public:
	Shape* CreateShape() override
	{
		return new Rectangle();
	}
};

class SimpleShapeFactory : public Factory {
public:
	Shape* CreateShape() override
	{
		return new Circle();
	}
};

class Paint
{
public:
	Paint();
	~Paint();
	void Start();
};
