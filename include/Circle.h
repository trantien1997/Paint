/***********************************************************
 *  Circle.h                                               *
 *  Created by Tien, NguyenTran on 07.20.2024.             *
 *  Copyright © 2024. All rights reserved.                 *
 ***********************************************************/

#pragma once

#include "Shape.h"
#include <string>
#include <vector>


class Circle : public Shape {
private:
  uint32_t centerX;
  uint32_t centerY;
  uint32_t radius;
  std::vector<Shape *> arrAddedCircle;
  std::vector<Shape *> arrRemovedCircle;

  void wrap(uint32_t &minValue, uint32_t &maxValue);
  void Add(Shape *shape);

public:
  Circle();

  Circle(const uint32_t &centerX, const uint32_t &centerY,
         const uint32_t &radius);

  void Add() override;

  void Remove() override;

  void Draw(Shape *shape) override;

  void RevertOperation() override;

  ~Circle();
};
