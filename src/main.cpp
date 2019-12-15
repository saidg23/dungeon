#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include "../headers/graphics.h"

int getRand(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main()
{
    srand(time(0));
    std::cout << "\e[1;1H\e[0J\e[1;1H";
    const int xres = 100;
    const int yres = 40;
    ImageBuffer test(xres, yres);

    std::vector<Vector2> points;
    int attempts = 0;
    int maxAttempts = 20;
    bool valid;
    while(attempts < maxAttempts)
    {
        valid = true;

        Vector2 newPoint(getRand(0, xres -1), getRand(0, yres -1));
        for(size_t i = 0; i < points.size(); ++i)
        {
            if((points[i] - newPoint).getMagnitude() < 25)
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

    for(size_t i = 0; i < points.size(); ++i)
    {
        test.setPixel(points[i], "*");
    }

    drawImage(test);

    return 0;
}
