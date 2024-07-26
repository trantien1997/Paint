/***********************************************************
 *  Circle.cpp                                             *
 *  Created by Tien, NguyenTran on 07.20.2024.             *
 *  Copyright © 2024. All rights reserved.                 *
 ***********************************************************/

#include "Circle.h"
#include "WindowApi.h"
#include <ctime>

Circle::Circle() {}

Circle::Circle(const uint32_t &centerX, const uint32_t &centerY,
               const uint32_t &radius) {
  this->centerX = centerX;
  this->centerY = centerY;
  this->radius = radius;
}

void Circle::Add() {
  srand(time(NULL));
  // Rangdom for radius
  uint32_t radius = rand() % (12 - 5 + 1) + 5;

  // Rangdom for centerX
  uint32_t minCenterX = 30 + int(radius);
  uint32_t maxCenterX = 86 - int(radius);
  if (minCenterX > maxCenterX)
    wrap(minCenterX, maxCenterX);
  uint32_t centerX = rand() % (maxCenterX - minCenterX + 1) + minCenterX;

  // Rangdom for centerY
  uint32_t minCenterY = 5 + int(radius);
  uint32_t maxCenterY = 22 - int(radius);
  if (minCenterY > maxCenterY)
    wrap(minCenterY, maxCenterY);
  uint32_t centerY = rand() % (maxCenterY - minCenterY + 1) + minCenterY;
  // Save Information of Circle Shape
  Shape *cir = new Circle(centerX, centerY, radius);
  arrAddedCircle.push_back(cir);

  // Save last operation of circle
  lastOperation = Operation::ADD;

  // Draw circle to console screen
  Draw(cir);
}

void Circle::Add(Shape *shape) {
  // Save Information of Rectangle Shape
  arrAddedCircle.push_back(shape);

  // Save last operation of rectangle
  lastOperation = Operation::ADD;

  // Draw rectangle to console screen
  Draw(shape);
}

void Circle::Remove() {
  if (!arrAddedCircle.size()) {
    std::cout << "Nothing to remove!" << std::endl;
    return;
  }

  Circle *cir = dynamic_cast<Circle *>(arrAddedCircle.back());
  uint32_t centerX = cir->centerX;
  uint32_t centerY = cir->centerY;
  uint32_t radius = cir->radius;

  // Remove the display of the last rectangle in arrAddedCircle
  float pr = 2; // pr is the aspected pixel ratio which is almost equal to 2
  for (int positionX = centerX - radius; positionX <= centerX + radius;
       positionX++) { // loop for horizontal movement
    int X = centerX - positionX;
    for (int positionY = centerY - radius; positionY <= centerY + radius;
         positionY++) { // loop for vertical movement
      int Y = centerY - positionY;
      WindowApi::gotoxy(positionX, positionY);
      float d =
          ((Y * pr) * (Y * pr)) / (radius * radius) +
          (X * X) / (radius * radius); // multiplying the i variable with pr to
                                       // equalize pixel-width with the height
      if (d > 0.95 && d < 1.08) { // determining if the point is in the circle
        std::cout << " ";
      }
    }
  }

  // Remove the last element of array
  arrAddedCircle.pop_back();

  // Save Information of Circle Shape
  arrRemovedCircle.push_back(arrAddedCircle.back());

  // Save last operation of circle
  lastOperation = Operation::REMOVE;
}

void Circle::Draw(Shape *shape) {
  Circle *cir = dynamic_cast<Circle *>(shape);
  float pr = 2; // pr is the aspected pixel ratio which is almost equal to 2
  uint32_t radius = cir->radius;
  uint32_t centerX = cir->centerX;
  uint32_t centerY = cir->centerY;
  for (int positionX = centerX - radius; positionX <= centerX + radius;
       positionX++) { // loop for horizontal movement1
    int X = centerX - positionX;
    for (int positionY = centerY - radius; positionY <= centerY + radius;
         positionY++) { // loop for vertical movement
      int Y = centerY - positionY;
      WindowApi::gotoxy(positionX, positionY);
      float d =
          ((Y * pr) * (Y * pr)) / (radius * radius) +
          (X * X) / (radius * radius); // multiplying the i variable with pr to
                                       // equalize pixel-width with the height
      if (d > 0.95 && d < 1.08) { // determining if the point is in the circle
        std::cout << "*";
      }
    }
  }
}

void Circle::RevertOperation() {
  if (!arrAddedCircle.size() || !arrRemovedCircle.size()) {
    std::cout << "Nothing to undo or redo" << std::endl;
    return;
  }

  switch (lastOperation) {
  case Operation::ADD: {
    Remove();
    break;
  }
  case Operation::REMOVE: {
    auto shape = arrRemovedCircle.back();
    Add(shape);
    // Remove shape from arrRemovedCircle
    arrRemovedCircle.pop_back();
    break;
  }
  default: {
    std::cout << "Cannot undo or redo" << std::endl;
  }
  }
}

void Circle::wrap(uint32_t &minValue, uint32_t &maxValue) {
  uint32_t temp = minValue;
  minValue = maxValue;
  maxValue = temp;
}
