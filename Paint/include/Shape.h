#include <iostream>

enum class Operation
{
	ADD,
	REMOVE,
	UNKNOWN
};
class Shape
{
protected:
    bool flagAdd{false};
    bool flagRemove{false};
    bool flagUndo{false};
    bool flagRedo{false};
public:
    virtual void Add() = 0;
    virtual void Remove() = 0;
    virtual void Draw(Shape *shape) = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;
};
