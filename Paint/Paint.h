/***********************************************************
 *  Paint.h                                                *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright © 2021 TranTien. All rights reserved.        *
 ***********************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#pragma warning(disable: 4996)

#define add    97
#define remove 114
#define undo   117
#define redo   98
#define modify 109
#define circle 99
#define Exit   113

using namespace std;

struct circle_
{
	int centerX, centerY;
	float radius;
};

struct rectangle_
{
	int centerX, centerY;
	int width, height;
};

vector<circle_> arrCircle;
vector<circle_> arrAddCircle;
vector<circle_> arrRemoveCircle;

vector<rectangle_> arrRectangle;
vector<rectangle_> arrAddRectangle;
vector<rectangle_> arrRemoveRectangle;

vector<circle_> undoAddCircle;
vector<circle_> undoRemoveCircle;

vector<rectangle_> undoAddRectangle;
vector<rectangle_> undoRemoveRectangle;

bool addRectangle;
bool removeRectangle;
bool addCircle;
bool removeCircle;
bool flagUndo = false;
bool flagRedo = false;
class Shape
{
public:
	virtual void Add() = 0;
	virtual void Draw() = 0;
	virtual void Undo(bool flagAdd, bool flagRemove) = 0;
	virtual void Redo(bool flagAdd, bool flagRemove) = 0;
	virtual void Remove() = 0;
};

// Create concrete classes implement Shape interface
class rectangle : public Shape
{
	public:
		rectangle();

		void Add();

		void Draw();

		void Undo(bool flagAdd, bool flagRemove);

		void Redo(bool flagAdd, bool flagRemove);

		void DrawRectangle(rectangle_ rect);

		void ClearRectangle(rectangle_ rect);

		void Remove();

		~rectangle();
};

class Circle : public Shape
{
	public:
		Circle();

		void Add();

		void Draw();

		void Undo(bool flagAdd, bool flagRemove);

		void Redo(bool flagAdd, bool flagRemove);

		void DrawCircle(circle_ cir);

		void ClearCircle(circle_ cir);

		void Remove();

		~Circle();
};

class Factory {
public:
	virtual Shape* createShape() = 0;
};

class SimpleShapeFactory : public Factory {
public:
	Shape* createShape();
};
class RobustShapeFactory : public Factory {
public:
	Shape* createShape();
};

Factory* ClientCode(Factory* factory, string Mode);

class Client {
	private:
		Factory* factory;

	public:
		Client(Factory* f);

		void Add();

		void Draw();

		Shape* Undo();

		Shape* Redo();

		void Remove();
};

void gotoxy(int x, int y);

void resizeConsole(int width, int height);

void ContourDrawing();

void Start();

void AddShape();

void RemoveShape();

void UndoShape();

void RedoShape();

/* Display information to the user interface  */
void Display();

/* Clear the information displayed on the UI */
void ClearInfor();

/* Allow the user modify information of the shapes are displayed */
void ModifyInforOfShape();

/* Reference the corrected value and the value stored in the array  */
void MappingData(int x, int y, int value);

void wrap(int& a, int& b);

/* Allow the user to move the cursor to the position to be corrected */
void PointMove(int x, int y);

/*************************************************************** 
*  Allow the user create a Circle object or Rectangle object   *
*    C: A Circle Object                                        *
*    Any key: A Rectangle Object                               *
****************************************************************/
string SelectShape();

/* Convert uppercase characters to lowercase */
char make_lowercase(char in);

char yourChoice;