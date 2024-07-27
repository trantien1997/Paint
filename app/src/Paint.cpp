/***********************************************************
 *  Paint.cpp                                              *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright © 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#include "Paint.h"

#include "WindowApi.h"

std::string App::lastShape{};

Client::Client() {}

Client::Client(Factory *f) { Client::factory = f; }

Shape *Client::CreateShape(const std::string &shapeType) {
  if (shapeType == "SIMPLE") {
    factory = new SimpleShapeFactory();
    return factory->CreateShape();
  } else if (shapeType == "ROBUST") {
    factory = new RobustShapeFactory();
    return factory->CreateShape();
  } else {
    return nullptr;
  }
}

void App::start() {
  Client *client = new Client();
  while (true) {
    if (kbhit()) {
      auto yourChoice = convertStringToEnum(std::to_string(getch()), optionMap, Option::UNKNOWN);
      switch (yourChoice) {
        case Option::ADD:
          addShape(client);
          break;
        case Option::REMOVE:
          removeShape(client);
          break;
        case Option::UNDO:
          undoShape(client);
          break;
        case Option::REDO:
          redoShape(client);
          break;
        case Option::MODIFY:
          // TODO: Update later
          // modifyInforOfShape(client);
          break;
        case Option::EXIT:
          exit(0);
          break;
        default:
          std::cout << "your choice is unknown" << std::endl;
          break;
      }
    }
  }
}

void App::addShape(Client *client) {
  lastShape = selectShape();
  auto shape = client->CreateShape(lastShape);
  if (shape != nullptr) {
    shape->Add();
  } else {
    std::cout << "Cannot add shape" << std::endl;
  }
}

void App::removeShape(Client *client) {
  lastShape = selectShape();
  auto shape = client->CreateShape(lastShape);
  if (shape != nullptr) {
    shape->Remove();
  } else {
    std::cout << "Cannot remove shape" << std::endl;
  }
}

void App::undoShape(Client *client) {
  auto shape = client->CreateShape(lastShape);
  std::cout << "TIEN DEBUG: call to RevertOperation" << std::endl;
  shape->RevertOperation();
}

void App::redoShape(Client *client) {
  auto shape = client->CreateShape(lastShape);
  shape->RevertOperation();
}

std::string App::selectShape() {
  auto shapeType = convertStringToEnum(std::to_string(getch()), shapeMap, ShapeType::UNKNOWN);
  switch (shapeType) {
    case ShapeType::CIRCLE:
      return "SIMPLE";
      break;
    case ShapeType::RECTANGLE:
      return "ROBUST";
      break;
    default:
      return "UNKNOWN";
      break;
  }
}

int main() {
  // Resize Width and Height of the Application Window
  WindowApi::resizeConsole(1140, 450);

  // Draw interface of the application
  WindowApi::ContourDrawing();

  App::start();

  system("pause");
  return 0;
}
