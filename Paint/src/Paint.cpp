/***********************************************************
 *  Paint.cpp                                              *
 *  Created by TranTien on 10.10.17.                       *
 *  Copyright © 2021 TranTien. All rights reserved.        *  
 ***********************************************************/

#include "Paint.h"

/* RECTANGLE FUNCTION */
rectangle::rectangle() {}

void rectangle::Add()
{
    int min;
    int max;
    rectangle_ temp;

    if (arrRectangle.size() == 5)
        return;

    srand(time(NULL));
    temp.width = rand() % (56 - 5 + 1) + 5;
    temp.height = rand() % (17 - 5 + 1) + 5;

    // Rangdom for centerX
    min = 30 + 2 * temp.width;
    max = 86 - 2 * temp.width;
    while (min > max)
    {
        temp.width = rand() % (56 - 5 + 1) + 5;
        min = 30 + 2 * temp.width;
        max = 86 - 2 * temp.width;
    }
    temp.centerX = rand() % (max - min + 1) + min;

    // Rangdom for centerY
    min = 5 + temp.height;
    max = 22 - temp.height;
    while (min > max)
    {
        temp.height = rand() % (17 - 5 + 1) + 5;
        min = 5 + temp.height;
        max = 22 - temp.height;
    }
    temp.centerY = rand() % (max - min + 1) + min;

    // Save Information of Rectangle Shape

    arrAddRectangle.push_back(temp);

    Draw();
}

void rectangle::Draw()
{
    rectangle_ temp;

    /* Undo Button*/
    if (flagUndo && !flagRedo)
    {
        if (!arrRemoveRectangle.size())
            return;

        temp.centerX = arrRemoveRectangle[arrRemoveRectangle.size() - 1].centerX;
        temp.centerY = arrRemoveRectangle[arrRemoveRectangle.size() - 1].centerY;
        temp.width = arrRemoveRectangle[arrRemoveRectangle.size() - 1].width;
        temp.height = arrRemoveRectangle[arrRemoveRectangle.size() - 1].height;

        arrRemoveRectangle.erase(arrRemoveRectangle.begin() + arrRemoveRectangle.size() - 1);

        // Save information of the shape to use for Redo function
        undoAddRectangle.push_back(temp);
        arrRectangle.push_back(temp);
    }
    /*Redo Button*/
    else if (!flagUndo && flagRedo)
    {
        if (!undoRemoveRectangle.size())
            return;

        temp.centerX = undoRemoveRectangle[undoRemoveRectangle.size() - 1].centerX;
        temp.centerY = undoRemoveRectangle[undoRemoveRectangle.size() - 1].centerY;
        temp.width = undoRemoveRectangle[undoRemoveRectangle.size() - 1].width;
        temp.height = undoRemoveRectangle[undoRemoveRectangle.size() - 1].height;

        arrRectangle.push_back(temp);

        // remove the last element of the undoRemoveRectangle vector
        undoRemoveRectangle.erase(undoRemoveRectangle.begin() + undoRemoveRectangle.size() - 1);
    }
    else if (!flagUndo && !flagRedo)
    {
        if (!arrAddRectangle.size())
            return;

        temp.centerX = arrAddRectangle[0].centerX;
        temp.centerY = arrAddRectangle[0].centerY;
        temp.width = arrAddRectangle[0].width;
        temp.height = arrAddRectangle[0].height;

        arrRectangle.push_back(arrAddRectangle[0]);

        arrAddRectangle.erase(arrAddRectangle.begin());
    }

    Display();

    DrawRectangle(temp);

    if (!flagUndo && !flagRedo)
    {
        addRectangle = true;
        removeRectangle = false;
        addCircle = false;
        removeCircle = false;
    }

    flagUndo = false;
    flagRedo = false;
}

void rectangle::Undo(bool flagAdd, bool flagRemove)
{
    if (flagAdd == true && flagRemove == false)
    {
        Remove();
    }
    else if (flagAdd == false && flagRemove == true)
    {
        Draw();
    }
}

void rectangle::Redo(bool flagAdd, bool flagRemove)
{
    if (flagAdd == true && flagRemove == false)
    {
        Remove();
    }
    else if (flagAdd == false && flagRemove == true)
    {
        Draw();
    }
}

void rectangle::DrawRectangle(rectangle_ rect)
{
    for (int x = rect.centerX - rect.width; x <= rect.centerX + rect.width; x++)
    {
        for (int y = rect.centerY - rect.height / 2; y <= rect.centerY + rect.height / 2; y++)
        {
            gotoxy(x, y);
            if (y == rect.centerY - rect.height / 2)
            {
                cout << "_";
            }
            else if (y == rect.centerY + rect.height / 2)
            {
                if (x == rect.centerX - rect.width || x == rect.centerX + rect.width)
                    cout << "|";
                else
                    cout << "_";
            }
            else if (x == rect.centerX - rect.width || x == rect.centerX + rect.width)
            {
                cout << "|";
            }
            else
            {
                cout << "";
            }
        }
    }
}

void rectangle::ClearRectangle(rectangle_ rect)
{
    // Remove the display of the first rectangle  in arrRectangle
    for (int x = rect.centerX - rect.width; x <= rect.centerX + rect.width; x++)
    {
        for (int y = rect.centerY - rect.height / 2; y <= rect.centerY + rect.height / 2; y++)
        {
            gotoxy(x, y);
            if (y == rect.centerY - rect.height / 2 || y == rect.centerY + rect.height / 2)
            {
                cout << " ";
            }
            if (x == rect.centerX - rect.width || x == rect.centerX + rect.width)
            {
                cout << " ";
            }
        }
    }
}

void rectangle::Remove()
{
    //int centerX, centerY;
    //int width, height;
    rectangle_ temp;

    if (!arrRectangle.size())
        return;

    /* Remove Button  */
    if (!flagUndo && !flagRedo)
    {
        // Get information of the first rectangle
        temp.centerX = arrRectangle[0].centerX;
        temp.centerY = arrRectangle[0].centerY;
        temp.width = arrRectangle[0].width;
        temp.height = arrRectangle[0].height;
    }
    /* Undo Button  */
    else if (flagUndo && !flagRedo)
    {
        // Get information of the final rectangle
        temp.centerX = arrRectangle[arrRectangle.size() - 1].centerX;
        temp.centerY = arrRectangle[arrRectangle.size() - 1].centerY;
        temp.width = arrRectangle[arrRectangle.size() - 1].width;
        temp.height = arrRectangle[arrRectangle.size() - 1].height;

        // Save information of Shape to Redo function use
        undoRemoveRectangle.push_back(temp);
    }
    /* Redo Button*/
    else if (!flagUndo && flagRedo)
    {
        // Get information of the final rectangle
        temp.centerX = undoAddRectangle[undoAddRectangle.size() - 1].centerX;
        temp.centerY = undoAddRectangle[undoAddRectangle.size() - 1].centerY;
        temp.width = undoAddRectangle[undoAddRectangle.size() - 1].width;
        temp.height = undoAddRectangle[undoAddRectangle.size() - 1].height;
    }
    else
    {
        // Do not something
    }

    ClearRectangle(temp);

    ClearInfor();
    if (!flagUndo && !flagRedo)
    {
        arrRemoveRectangle.push_back(arrRectangle[0]);
        arrRectangle.erase(arrRectangle.begin());
    }
    else if (flagUndo && !flagRedo)
    {
        arrRectangle.erase(arrRectangle.begin() + arrRectangle.size() - 1);
    }
    else if (!flagUndo && flagRedo)
    {
        arrRectangle.erase(arrRectangle.begin() + arrRectangle.size() - 1);
        undoAddRectangle.erase(undoAddRectangle.begin() + undoAddRectangle.size() - 1);
    }

    Display();

    if (!flagUndo && !flagRedo)
    {
        addRectangle = false;
        removeRectangle = true;
        addCircle = false;
        removeCircle = false;
    }
    flagUndo = false;
    flagRedo = false;
}

rectangle::~rectangle() {}

/* CIRCLE FUNCTION */
Circle::Circle() {}

void Circle::Add()
{
    int min, max;
    circle_ temp;

    if (arrCircle.size() == 4)
        return;

    /*Add Button*/
    // Random for radius
    srand(time(NULL));
    temp.radius = rand() % (12 - 5 + 1) + 5;

    // Rangdom for centerX
    min = 30 + int(temp.radius);
    max = 86 - int(temp.radius);
    if (min > max)
        wrap(min, max);
    temp.centerX = rand() % (max - min + 1) + min;

    // Rangdom for centerY
    min = 5 + int(temp.radius);
    max = 22 - int(temp.radius);
    if (min > max)
        wrap(min, max);
    temp.centerY = rand() % (max - min + 1) + min;

    arrAddCircle.push_back(temp);

    Draw();
}

void Circle::Draw()
{
    int min, max;
    circle_ temp;

    /*Undo Button*/
    if (flagUndo && !flagRedo)
    {
        if (!arrRemoveCircle.size())
            return;

        temp.centerX = arrRemoveCircle[arrRemoveCircle.size() - 1].centerX;
        temp.centerY = arrRemoveCircle[arrRemoveCircle.size() - 1].centerY;
        temp.radius = arrRemoveCircle[arrRemoveCircle.size() - 1].radius;

        arrRemoveCircle.erase(arrRemoveCircle.begin() + arrRemoveCircle.size() - 1);

        undoAddCircle.push_back(temp);
        arrCircle.push_back(temp);
    }
    /*Redo Button*/
    else if (!flagUndo && flagRedo)
    {
        if (!undoRemoveCircle.size())
            return;
        temp.centerX = undoRemoveCircle[undoRemoveCircle.size() - 1].centerX;
        temp.centerY = undoRemoveCircle[undoRemoveCircle.size() - 1].centerY;
        temp.radius = undoRemoveCircle[undoRemoveCircle.size() - 1].radius;

        arrCircle.push_back(temp);

        undoRemoveCircle.erase(undoRemoveCircle.begin() + undoRemoveCircle.size() - 1);
    }
    else if (!flagUndo && !flagRedo)
    {
        if (!arrAddCircle.size())
            return;

        temp.centerX = arrAddCircle[0].centerX;
        temp.centerY = arrAddCircle[0].centerY;
        temp.radius = arrAddCircle[0].radius;

        arrCircle.push_back(arrAddCircle[0]);

        arrAddCircle.erase(arrAddCircle.begin());
    }

    Display();

    DrawCircle(temp);

    if (!flagUndo && !flagRedo)
    {
        addRectangle = false;
        removeRectangle = false;
        addCircle = true;
        removeCircle = false;
    }

    flagUndo = false;
    flagRedo = false;
}

void Circle::Undo(bool flagAdd, bool flagRemove)
{
    if (flagAdd == true && flagRemove == false)
    {
        Remove();
    }
    else if (flagAdd == false && flagRemove == true)
    {
        Draw();
    }
}

void Circle::Redo(bool flagAdd, bool flagRemove)
{
    if (flagAdd == true && flagRemove == false)
    {
        Remove();
    }
    else if (flagAdd == false && flagRemove == true)
    {
        Draw();
    }
}

void Circle::DrawCircle(circle_ cir)
{
    float pr = 2; // pr is the aspected pixel ratio which is almost equal to 2
    for (int x = cir.centerX - cir.radius; x <= cir.centerX + cir.radius; x++) // loop for horizontal movement1   
    {
        int X = cir.centerX - x;
        for (int y = cir.centerY - cir.radius; y <= cir.centerY + cir.radius; y++) // loop for vertical movement
        {
            int Y = cir.centerY - y;
            gotoxy(x, y);
            float d = ((Y * pr) * (Y * pr)) / (cir.radius * cir.radius) + (X * X) / (cir.radius * cir.radius); //multiplying the i variable with pr to equalize pixel-width with the height
            if (d > 0.95 && d < 1.08) // approximation
            {
                cout << "*";
            }
        }
    }
}

void Circle::ClearCircle(circle_ cir)
{
    float pr = 2; // pr is the aspected pixel ratio which is almost equal to 2
    for (int x = cir.centerX - cir.radius; x <= cir.centerX + cir.radius; x++) // loop for horizontal movement1   
    {
        int X = cir.centerX - x;
        for (int y = cir.centerY - cir.radius; y <= cir.centerY + cir.radius; y++) // loop for vertical movement
        {
            int Y = cir.centerY - y;
            gotoxy(x, y);
            float d = ((Y * pr) * (Y * pr)) / (cir.radius * cir.radius) + (X * X) / (cir.radius * cir.radius); //multiplying the i variable with pr to equalize pixel-width with the height
            if (d > 0.95 && d < 1.08) // approximation
            {
                cout << " ";
            }
        }
    }
}

void Circle::Remove()
{
    circle_ temp;

    if (!arrCircle.size())
        return;

    /* Remove Button */
    if (!flagUndo && !flagRedo)
    {
        // Get information of the first circle
        temp.centerX = arrCircle[0].centerX;
        temp.centerY = arrCircle[0].centerY;
        temp.radius = arrCircle[0].radius;
    }
    /* Undo Button */
    else if (flagUndo && !flagRedo)
    {
        // Get information of the final circle
        temp.centerX = arrCircle[arrCircle.size() - 1].centerX;
        temp.centerY = arrCircle[arrCircle.size() - 1].centerY;
        temp.radius = arrCircle[arrCircle.size() - 1].radius;

        // Save infortion of Shape to Redo function use
        undoRemoveCircle.push_back(temp);
    }
    /* Redo Button*/
    else if (!flagUndo && flagRedo)
    {
        temp.centerX = undoAddCircle[undoAddCircle.size() - 1].centerX;
        temp.centerY = undoAddCircle[undoAddCircle.size() - 1].centerY;
        temp.radius = undoAddCircle[undoAddCircle.size() - 1].radius;
    }
    else
    {
        // Do not something
    }

    ClearCircle(temp);

    ClearInfor();
    if (!flagUndo && !flagRedo)
    {
        arrRemoveCircle.push_back(arrCircle[0]);
        arrCircle.erase(arrCircle.begin());
    }
    else if (flagUndo && !flagRedo)
    {
        arrCircle.erase(arrCircle.begin() + arrCircle.size() - 1);
    }
    else if (!flagUndo && flagRedo)
    {
        arrCircle.erase(arrCircle.begin() + arrCircle.size() - 1);
        undoAddCircle.erase(undoAddCircle.begin() + undoAddCircle.size() - 1);
    }
    Display();

    if (!flagUndo && !flagRedo)
    {
        addRectangle = false;
        removeRectangle = false;
        addCircle = false;
        removeCircle = true;
    }
    flagUndo = false;
    flagRedo = false;
}

Circle::~Circle() {}

/* FACTORY FUNCTION */
Shape* SimpleShapeFactory::createShape()
{
    return new Circle;
}

Shape* RobustShapeFactory::createShape()
{
    return new rectangle;
}

Factory* ClientCode(Factory* factory, string Mode)
{
    if (Mode == "SIMPLE")
        factory = new SimpleShapeFactory;
    else if (Mode == "ROBUST")
        factory = new RobustShapeFactory;
    return factory;
}

/* CLIENT FUNCTION*/
Client::Client(Factory* f)
{
    Client::factory = f;
}

void Client::Add()
{
    Shape* w = Client::factory->createShape();
    w->Add();
}

void Client::Draw()
{
    Shape* w = Client::factory->createShape();
    w->Draw();
}

Shape* Client::Undo()
{
    Shape* w = Client::factory->createShape();
    return w;
}

Shape* Client::Redo()
{
    Shape* w = Client::factory->createShape();
    return w;
}

void Client::Remove()
{
    Shape* w = Client::factory->createShape();
    w->Remove();
}

/* HANDLER FUNCTION */
void ContourDrawing()
{
    ifstream fin;
    string line;
    fin.open("GUI.txt");

    while (fin)
    {
        getline(fin, line);
        cout << line << endl;
    }
}

void Display()
{
    // Display information of Circle shape
    gotoxy(9, 5);
    cout << arrCircle.size();
    for (int i = 0; i < arrCircle.size(); i++)
    {
        gotoxy(3, 7 + i);
        cout << "(" << arrCircle[i].centerX << "," << arrCircle[i].centerY << ")";
    }

    for (int i = 0; i < arrCircle.size(); i++)
    {
        gotoxy(17, 7 + i);
        cout << arrCircle[i].radius;
    }

    // Display information of Rectangle shape
    gotoxy(12, 15);
    cout << arrRectangle.size();
    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(3, 17 + i);
        cout << "(" << arrRectangle[i].centerX << "," << arrRectangle[i].centerY << ")";
    }

    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(15, 17 + i);
        cout << arrRectangle[i].width;
    }

    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(24, 17 + i);
        cout << arrRectangle[i].height;
    }
}

void ClearInfor()
{
    // Clear information of Circle shape
    gotoxy(9, 5);
    cout << 0;
    for (int i = 0; i < arrCircle.size(); i++)
    {
        gotoxy(3, 7 + i);
        cout << "       ";
    }

    for (int i = 0; i < arrCircle.size(); i++)
    {
        gotoxy(17, 7 + i);
        cout << "  ";
    }

    // Display information of Rectangle shape
    gotoxy(12, 15);
    cout << 0;
    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(3, 17 + i);
        cout << "       ";;
    }

    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(15, 17 + i);
        cout << "  ";
    }

    for (int i = 0; i < arrRectangle.size(); i++)
    {
        gotoxy(24, 17 + i);
        cout << "  ";
    }
}

void Start()
{
    while (true)
    {
        if (kbhit())
        {
            yourChoice = getch();
            yourChoice = make_lowercase(yourChoice);
            if (yourChoice == add)
            {
                AddShape();
            }
            else if (yourChoice == remove)
            {
                RemoveShape();
            }
            else if (yourChoice == undo)
            {
                UndoShape();
            }
            else if (yourChoice == redo)
            {
                RedoShape();
            }
            else if (yourChoice == modify)
            {
                ModifyInforOfShape();
            }
            else if(yourChoice == Exit)
            {
                exit(0);
            }
        }
    }
}

void AddShape()
{
    string selecteShape;
    Factory* factory = NULL;
    selecteShape = SelectShape();
    factory = ClientCode(factory, selecteShape);
    Client* c = new Client(factory);
    c->Add();
}

void UndoShape()
{
    Factory* factory = NULL;
    bool flagAdd, flagRemove;

    if (!arrCircle.size() && addCircle == true)
        return;

    if (!arrRemoveCircle.size() && removeCircle == true)
        return;

    if (!arrRectangle.size() && addRectangle == true)
        return;

    if (!arrRemoveRectangle.size() && removeRectangle == true)
        return;

    flagUndo = true;

    if ((addRectangle == true || removeRectangle == true) && addCircle == false && removeCircle == false)
    {
        factory = ClientCode(factory, "ROBUST");
    }
    else if (addRectangle == false && removeRectangle == false && (addCircle == true || removeCircle == true))
    {
        factory = ClientCode(factory, "SIMPLE");
    }
    else
    {
        flagUndo = false;
        return;
    }

    Client* c = new Client(factory);

    Shape* shape = c->Undo();

    if (addCircle == true || addRectangle == true)
    {
        flagAdd = true;
        flagRemove = false;
    }
    else if (removeCircle == true || removeRectangle == true)
    {
        flagAdd = false;
        flagRemove = true;
    }

    shape->Undo(flagAdd, flagRemove);
}

void RedoShape()
{
    Factory* factory = NULL;
    bool flagAdd = false, flagRemove = false;

    if (!undoAddCircle.size() && !undoRemoveCircle.size() && !undoAddRectangle.size() && !undoRemoveRectangle.size())
        return;

    flagRedo = true;

    if (undoAddRectangle.size() || undoRemoveRectangle.size())
    {
        factory = ClientCode(factory, "ROBUST");
    }
    else if (undoAddCircle.size() || undoRemoveCircle.size())
    {
        factory = ClientCode(factory, "SIMPLE");
    }
    else
    {
        return;
    }

    if (undoAddRectangle.size() || undoAddCircle.size())
        flagAdd = true;
    else
        flagRemove = true;

    Client* client = new Client(factory);

    Shape* shape = client->Redo();

    shape->Redo(flagAdd, flagRemove);
}

void RemoveShape()
{
    string selecteShape;
    Factory* factory = NULL;
    selecteShape = SelectShape();
    factory = ClientCode(factory, selecteShape);
    Client* c = new Client(factory);
    c->Remove();
}

string SelectShape()
{
    char selectShape;

    selectShape = getch();
    selectShape = make_lowercase(selectShape);
    if (selectShape == circle)
    {
        return "SIMPLE";
    }
    else
    {
        return "ROBUST";
    }
}

void ModifyInforOfShape()
{
    int x = 3;
    int y = 7;
    vector<rectangle_> tempRec;
    vector<circle_> tempCir;

    // Back up the rectangles before changing 
    if (arrRectangle.size())
    {
        for (int i = 0; i < arrRectangle.size(); i++)
            tempRec.push_back(arrRectangle[i]);
    }

    // Back up the circles before changing 
    if (arrCircle.size())
    {
        for (int i = 0; i < arrCircle.size(); i++)
            tempCir.push_back(arrCircle[i]);
    }

    gotoxy(x, y);

    PointMove(x, y);

    // Clear these previous rectangles
    for (int i = 0; i < tempRec.size(); i++)
    {
        rectangle* rect = new rectangle;
        rect -> ClearRectangle(tempRec[i]);
        delete rect;
    }

    // Draw these update rectangle
    for (int i = 0; i < arrRectangle.size(); i++)
    {
        rectangle* rect = new rectangle;
        rect -> DrawRectangle(arrRectangle[i]);
        delete rect;
    }

    // Clear these previous circle
    for (int i = 0; i < tempCir.size(); i++)
    {
        Circle* cir = new Circle;
        cir -> ClearCircle(tempCir[i]);
        delete cir;
    }

    // Draw these update circle
    for (int i = 0; i < arrCircle.size(); i++)
    {
        Circle* cir = new Circle;
        cir -> DrawCircle(arrCircle[i]);
        delete cir;
    }
}

void PointMove(int x, int y)
{
    while (1)
    {
        char c = getch();
        if (c == -32)
        {
            c = getch();
            if (c == 75)
            {
                if (x > 0)
                    x--;
            }
            else if (c == 77)
            {
                if (x < 1100)
                    x++;
            }
            else if (c == 72)
            {
                if (y > 0)
                    y--;
            }
            else if (c == 80)
            {
                if (y < 420)
                    y++;
            }
            gotoxy(x, y);
        }
        else if (c == 9)
        {
            int data;
            cin >> data;
            gotoxy(x, y);
            cout << data;
            MappingData(x, y, data);
        }
        else if (c == 101)
            break;
    }
}

void MappingData(int x, int y, int value)
{
    // CIRCLE
    if (x == 4 && y == 7)
        arrCircle[0].centerX = value;
    if (x == 7 && y == 7)
        arrCircle[0].centerY = value;
    if (x == 17 && y == 7)
        arrCircle[0].radius = value;

    if (x == 4 && y == 8)
        arrCircle[1].centerX = value;
    if (x == 7 && y == 8)
        arrCircle[1].centerY = value;
    if (x == 17 && y == 8)
        arrCircle[1].radius = value;

    if (x == 4 && y == 9)
        arrCircle[2].centerX = value;
    if (x == 7 && y == 9)
        arrCircle[2].centerY = value;
    if (x == 17 && y == 9)
        arrCircle[2].radius = value;

    if (x == 4 && y == 10)
        arrCircle[3].centerX = value;
    if (x == 7 && y == 10)
        arrCircle[3].centerY = value;
    if (x == 17 && y == 10)
        arrCircle[3].radius = value;

    // RECTANGLE
    if (x == 4 && y == 17)
        arrRectangle[0].centerX = value;
    if (x == 7 && y == 17)
        arrRectangle[0].centerY = value;
    if (x == 15 && y == 17)
        arrRectangle[0].width = value;
    if (x == 24 && y == 17)
        arrRectangle[0].height = value;

    if (x == 4 && y == 18)
        arrRectangle[1].centerX = value;
    if (x == 7 && y == 18)
        arrRectangle[1].centerY = value;
    if (x == 15 && y == 18)
        arrRectangle[1].width = value;
    if (x == 24 && y == 18)
        arrRectangle[1].height = value;

    if (x == 4 && y == 19)
        arrRectangle[2].centerX = value;
    if (x == 7 && y == 19)
        arrRectangle[2].centerY = value;
    if (x == 15 && y == 19)
        arrRectangle[2].width = value;
    if (x == 24 && y == 19)
        arrRectangle[2].height = value;

    if (x == 4 && y == 20)
        arrRectangle[3].centerX = value;
    if (x == 7 && y == 20)
        arrRectangle[3].centerY = value;
    if (x == 15 && y == 20)
        arrRectangle[3].width = value;
    if (x == 24 && y == 20)
        arrRectangle[3].height = value;

    if (x == 4 && y == 21)
        arrRectangle[4].centerX = value;
    if (x == 7 && y == 21)
        arrRectangle[4].centerY = value;
    if (x == 15 && y == 21)
        arrRectangle[4].width = value;
    if (x == 24 && y == 21)
        arrRectangle[4].height = value;
}

void wrap(int& a, int& b)  // only in C++, file .cpp
{
    int temp = a;
    a = b;
    b = temp;
}

char make_lowercase(char in)
{
    if (in >= 65 && in <= 90)
        in = in + 32;
    return in;
}

/* MAIN FUNCTION */
int main()
{
    // Resize Width and Height of the Application Window 
    WindowApi::resizeConsole(1140, 450);

    // Draw interface of the application
    ContourDrawing();

    Start();

    system("pause");
    return 0;
}
