/***********************************************************
 *  Paint.h                                                *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright � 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#pragma once

#include <conio.h>
#include "Circle.h"
#include "Rectangle.h"

class Factory {
 public:
  virtual Shape *CreateShape() = 0;
};

class RobustShapeFactory : public Factory {
 public:
  Shape *CreateShape() override { return new Rectangle(); }
};

class SimpleShapeFactory : public Factory {
 public:
  Shape *CreateShape() override { return new Circle(); }
};

class Client {
 public:
  Factory *factory;
  Client();
  Client(Factory *f);
  Shape *CreateShape(std::string shapeType);
};

class App {
 public:
  static std::string lastShape;
  static char yourChoice;
  static void start();
  static void addShape(Client *client);
  static void removeShape(Client *client);
  static void undoShape(Client *client);
  static void redoShape(Client *client);
  static void modifyInforOfShape(Client *client);
  static std::string selectShape();
};
