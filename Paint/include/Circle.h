#include "Shape.h"

class Circle : public Shape
{
private:
    uint32_t centerX;
    uint32_t centerY;
    uint32_t radius;
public:
		Circle();

		void Add() override;

		void Remove() override;

		void Draw() override;

		void Undo(bool flagAdd, bool flagRemove);

		void Redo(bool flagAdd, bool flagRemove);

		void DrawCircle(const uint32_t &centerX, const uint32_t &centerY, const uint32_t &radius);

		void ClearCircle(const uint32_t &centerX, const uint32_t &centerY, const uint32_t &radius);

		~Circle();
};