#include "Rectangle.h"
#include "WindowApi.h"

Rectangle::Rectangle(const uint32_t &centerX, const uint32_t &centerY, const uint32_t &width, const uint32_t &height)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->width = width;
    this->height = height;
}

void Rectangle::Add() {
    srand(time(NULL));
    uint32_t width = rand() % (56 - 5 + 1) + 5;
    uint32_t height = rand() % (17 - 5 + 1) + 5;

    // Rangdom for centerX
    uint32_t minCenterX = 30 + 2 * width;
    uint32_t maxCenterX = 86 - 2 * width;
    while (minCenterX > maxCenterX) {
        width = rand() % (56 - 5 + 1) + 5;
        minCenterX = 30 + 2 * width;
        maxCenterX = 86 - 2 * width;
    }
    uint32_t centerX = rand() % (maxCenterX - minCenterX + 1) + minCenterX;

    // Rangdom for centerY
    uint32_t minCenterY = 5 + height;
    uint32_t maxCenterY = 22 - height;
    while (minCenterY > maxCenterY) {
        height = rand() % (17 - 5 + 1) + 5;
        minCenterY = 5 + height;
        maxCenterY = 22 - height;
    }
    uint32_t centerY = rand() % (maxCenterY - minCenterY + 1) + minCenterY;

    // Save Information of Rectangle Shape
    Shape* rec = new Rectangle(centerX, centerY, width, height);
    arrAddedRectangle.push_back(rec);

    // Save last operation of rectangle
    lastOperation = Operation::ADD;

    // Draw rectangle to console screen
    Draw(rec);
}

void Rectangle::Add(Rectangle *rect) {

}

void Rectangle::Remove() {
    if (!arrAddedRectangle.size()) {
        std::cout << "Nothing to remove!" << std::endl;
        return;
    }

    Rectangle* rect = dynamic_cast<Rectangle*>(arrAddedRectangle.back());

    // Remove rectangle from arrAddedRectangle
    arrAddedRectangle.pop_back();

    // Remove the display of the last rectangle in arrAddedRectangle
    for (int positonX = rect->centerX - rect->width; positonX <= rect->centerX + rect->width; positonX++) {
        for (int positonY = rect->centerY - rect->height / 2; positonY <= rect->centerY + rect->height / 2; positonY++) {
            WindowApi::gotoxy(positonX, positonY);
            if (positonY == rect->centerY - rect->height / 2 || positonY == rect->centerY + rect->height / 2) {
                std::cout << " ";
            } else if (positonX == rect->centerX - rect->width || positonX == rect->centerX + rect->width) {
                std::cout << " ";
            } else {
                std::cout << " ";
            }
        }
    }

    // Save last operation of rectangle
    lastOperation = Operation::REMOVE;

    // Save removed rectangle to arrRemovedRectangle
    Shape* rec = new Rectangle(rect->centerX, rect->centerY, rect->width, rect->height);
    arrRemovedRectangle.push_back(rec);
}

void Rectangle::Undo() {
    if (!arrRemovedRectangle.size() || !arrAddedRectangle.size()) {
        std::cout << "Nothing to undo!" << std::endl;
        return;
    }

    switch(lastOperation) {
        case Operation::ADD:
            Remove();
            break;
        case Operation::REMOVE:
            auto rect = dynamic_cast<Rectangle*>(arrRemovedRectangle.back());
            Add(rect);
            break;
        default:
            std::cout << "Cannot undo!" << std::endl;
            break;
    }
}

void Rectangle::Draw(Shape *shape) {
    Rectangle* rect = dynamic_cast<Rectangle*>(shape);

    for (int positonX = rect->centerX - rect->width; positonX <= rect->centerX + rect->width; positonX++) {
        for (int positonY = rect->centerY - rect->height / 2; positonY <= rect->centerY + rect->height / 2; positonY++) {
            WindowApi::gotoxy(positonX, positonY);

            if (positonY == rect->centerY - rect->height / 2) {
                std::cout << horizontalBar;
            } else if (positonY == rect->centerY + rect->height / 2) {
                if (positonX == rect->centerX - rect->width || positonX == rect->centerX + rect->width) {
                    std::cout << verticalBar;
                } else {
                    std::cout << horizontalBar;
                }
            } else if (positonX == rect->centerX - rect->width || positonX == rect->centerX + rect->width) {
                std::cout << verticalBar;
            }
        }
    }
}
