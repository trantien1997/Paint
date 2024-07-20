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
    std::vector<Shape*> arrAddedRectangle;
    std::vector<Shape*> arrRemovedRectangle;

    void Add(Shape *shape);

public:
		Rectangle(const uint32_t &centerX, const uint32_t &centerY, const uint32_t &width, const uint32_t &height);

		void Add() override;

        void Remove() override;

		void Draw(Shape *shape) override;

		void RevertOperation() override;

		~Rectangle();
};
