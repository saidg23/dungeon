#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include "../headers/graphics.h"

enum Directions
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

double getRand(double min, double max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return rand() * fraction * (max - min + 1) + min;
}

struct Room
{
    int xpos;
    int ypos;
    int width;
    int height;
};

template <typename T>
struct Tree
{
    T data;
    Tree<T>* leftBranch = nullptr;
    Tree<T>* rightBranch = nullptr;
};

void genDungeon(Tree<Room> &tree, int depth, int xpos, int ypos, int width, int height)
{
    if(depth == 0)
    {
        tree.data.xpos = xpos;
        tree.data.ypos = ypos;
        tree.data.width = width;
        tree.data.height = height;
        return;
    }

    tree.leftBranch = new Tree<Room>;
    tree.rightBranch = new Tree<Room>;

    int direction = getRand(0, 2);

    if(direction == 0)
    {
        genDungeon(*tree.leftBranch, depth - 1, xpos, ypos, width, height/2);
        genDungeon(*tree.rightBranch, depth - 1, xpos, ypos + height / 2, width, height/2);
    }
    else
    {
        genDungeon(*tree.leftBranch, depth - 1, xpos, ypos, width / 2, height);
        genDungeon(*tree.rightBranch, depth - 1, xpos + width / 2, ypos, width / 2, height);
    }
}

void drawDungeon(ImageBuffer &img, Tree<Room> &tree)
{
    if(tree.leftBranch == nullptr)
    {
        img.drawRect(tree.data.xpos, tree.data.ypos, tree.data.width, tree.data.height);
        return;
    }
    else
    {
        drawDungeon(img, *tree.leftBranch);
        drawDungeon(img, *tree.rightBranch);
    }
}

int main()
{
    srand(time(0));
    std::cout << "\e[1;1H\e[0J\e[1;1H";
    const int xres = 80;
    const int yres = 40;
    ImageBuffer test(xres, yres);

    Tree<Room> dungeon;
    genDungeon(dungeon, 3, 0, 0, xres, yres);
    drawDungeon(test, dungeon);

    drawImage(test);

    return 0;
}
