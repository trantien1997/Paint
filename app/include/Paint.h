/***********************************************************
 *  Paint.h                                                *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright � 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#pragma once

#include <conio.h>

#include <unordered_map>

#include "Circle.h"
#include "Rectangle.h"

enum class Option {
  ADD,
  REMOVE,
  UNDO,
  REDO,
  MODIFY,
  EXIT,
  UNKNOWN
};

enum class ShapeType {
  CIRCLE,
  RECTANGLE,
  UNKNOWN
};

std::unordered_map<std::string, Option> optionMap = {
    {"a", Option::ADD},
    {"r", Option::REMOVE},
    {"u", Option::UNDO},
    {"re", Option::REDO},
    {"m", Option::MODIFY},
    {"q", Option::EXIT}
};

std::unordered_map<std::string, ShapeType> shapeMap = {
    {"c", ShapeType::CIRCLE},
    {"r", ShapeType::RECTANGLE}
};

template <class T>
T convertStringToEnum(const std::string &str, const std::unordered_map<std::string, T> &map, const T &defaultValue) {
  auto it = map.find(str);
  if (it != map.end()) {
    return it->second;
  }
  return defaultValue;
}

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
  Shape *CreateShape(const std::string &shapeType);
};

class App {
 public:
  static std::string lastShape;
  static void start();
  static void addShape(Client *client);
  static void removeShape(Client *client);
  static void undoShape(Client *client);
  static void redoShape(Client *client);
  static void modifyInforOfShape(Client *client);
  static std::string selectShape();
};
