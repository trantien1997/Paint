/***********************************************************
 *  Shape.h                                                *
 *  Created by Tien, NguyenTran on 07.20.2024.             *
 *  Copyright © 2024. All rights reserved.                 *
 ***********************************************************/

#pragma once

#include <iostream>

enum class Operation
{
	ADD,
	REMOVE,
	UNKNOWN
};
class Shape
{
protected:
    Operation lastOperation;
public:
    virtual void Add() = 0;
    virtual void Remove() = 0;
    virtual void Draw(Shape *shape) = 0;
    virtual void RevertOperation() = 0;
};
