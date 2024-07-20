#include "Shape.h"
#include <vector>
#include <string>

const static std::string verticalBar = "|";
const static std::string horizontalBar = "_";
class Rectangle : public Shape
{
private:
    uint32_t centerX;
    uint32_t centerY;
    uint32_t width;
    uint32_t height;
    Operation lastOperation;
    std::vector<Shape*> arrAddedRectangle;
    std::vector<Shape*> arrRemovedRectangle;
    std::vector<Shape*> undoAddRectangle;
    std::vector<Shape*> undoRemoveRectangle;

    void Add(Rectangle *rect);

public:
		Rectangle(const uint32_t &centerX, const uint32_t &centerY, const uint32_t &width, const uint32_t &height);

		void Add() override;

        void Remove() override;

		void Draw(Shape *shape) override;

		void Undo() override;

		void Redo() override;

		~Rectangle();
};
