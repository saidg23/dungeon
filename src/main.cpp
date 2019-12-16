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

int getRand(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int getDirection(double angle)
{
    if(angle <= 45 || angle > 315)
    {
        return RIGHT;
    }
    if(angle > 45 && angle <= 135)
    {
        return DOWN;
    }
    if(angle > 135 && angle <= 225)
    {
        return LEFT;
    }
    else
    {
        return UP;
    }
}

int main()
{
    srand(time(0));
    std::cout << "\e[1;1H\e[0J\e[1;1H";
    const int xres = 80;
    const int yres = 40;
    ImageBuffer test(xres, yres);

    std::vector<Vector2> points;
    int attempts = 0;
    int maxAttempts = 90;
    bool valid;

    while(attempts < maxAttempts)
    {
        valid = true;

        Vector2 newPoint(getRand(8, xres - 9), getRand(4, yres - 5));
        for(size_t i = 0; i < points.size(); ++i)
        {
            if((points[i] - newPoint).getMagnitude() < 24)
            {
                valid = false;
                attempts++;
                break;
            }
        }

        if(valid)
        {
            points.push_back(newPoint);
            attempts = 0;
        }
    }

    std::vector<std::vector<int>> limits;
    for(size_t i = 0; i < points.size(); ++i)
    {
        limits.push_back(std::vector<int>());
        limits.push_back(std::vector<int>());
        limits.push_back(std::vector<int>());
        limits.push_back(std::vector<int>());

        limits[i].push_back(0);
        limits[i].push_back(yres - 1);
        limits[i].push_back(0);
        limits[i].push_back(xres - 1);
        std::cout << "fine\n";
    }

    for(size_t i = 0; i < points.size(); ++i)
    {
        for(size_t j = 0; j < points.size(); ++j)
        {
            if(i == j)
            {
                continue;
            }

            Vector2 difference = points[j] - points[i];
            double angle = difference.getAngle() * (180.0 / M_PI);
            int dir = getDirection(angle);
            Vector2 midPoint = difference.scale(0.5) + points[i];

            if(dir == UP)
            {
                if(midPoint.y > limits[i][UP])
                {
                    limits[i][UP] = midPoint.y;
                }
            }
            else if(dir == DOWN)
            {
                if(midPoint.y < limits[i][DOWN])
                {
                    limits[i][DOWN] = midPoint.y;
                }
            }
            else if(dir == LEFT)
            {
                if(midPoint.x > limits[i][LEFT])
                {
                    limits[i][LEFT] = midPoint.x;
                }
            }
            else
            {
                if(midPoint.x < limits[i][RIGHT])
                {
                    limits[i][RIGHT] = midPoint.x;
                }
            }
        }
    }

    for(size_t i = 0; i < points.size(); ++i)
    {
        int xpos = getRand(limits[i][LEFT], static_cast<int>(points[i].x));
        int ypos = getRand(limits[i][UP], static_cast<int>(points[i].y));
        int maxWidth = limits[i][RIGHT] - xpos;
        int maxHeight = limits[i][DOWN] - ypos;
        int width = getRand(0.7 * maxWidth, maxWidth);
        int height = getRand(0.7 * maxHeight, maxHeight);
        test.drawRect(xpos, ypos, width, height);
    }

    drawImage(test);

    return 0;
}
