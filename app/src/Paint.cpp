/***********************************************************
 *  Paint.cpp                                              *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright © 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#include "Paint.h"
#include "WindowApi.h"

char App::yourChoice{};
std::string App::lastShape{};

Client::Client() {}

Client::Client(Factory *f) { Client::factory = f; }

Shape *Client::CreateShape(std::string shapeType) {
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
      yourChoice = getch();
      std::cout << "Your choice: " << yourChoice << std::endl;
      if (yourChoice == 'a') {
        addShape(client);
      } else if (yourChoice == 'r') {
        removeShape(client);
      } else if (yourChoice == 'u') {
        undoShape(client);
      } else if (yourChoice == 're') {
        redoShape(client);
      } else if (yourChoice == 'm') {
        // modifyInforOfShape(client);
      } else if (yourChoice == 'q') {
        exit(0);
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
  shape->RevertOperation();
}

void App::redoShape(Client *client) {
  auto shape = client->CreateShape(lastShape);
  shape->RevertOperation();
}

std::string App::selectShape() {
  yourChoice = getch();
  std::cout << "shape: " << yourChoice << std::endl;
  if (yourChoice == 'c') {
    return "SIMPLE";
  } else {
    return "ROBUST";
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
