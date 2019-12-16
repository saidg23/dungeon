#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cmath>

class Vector2
{
public:
    double x;
    double y;

    Vector2(double n_x, double n_y): x(n_x), y(n_y){}

    Vector2 scale(double multiplier)
    {
        x *= multiplier;
        y *= multiplier;
        return Vector2(x, y);
    }

    double getMagnitude()
    {
        return sqrt(x * x + y * y);
    }

    double getAngle()
    {
        if(y >=0)
        {
            return atan2(y, x);
        }
        else
        {
            return  2 * M_PI + atan2(y, x);
        }
    }
};

Vector2 operator+(Vector2 a, Vector2 b);

Vector2 operator-(Vector2 a, Vector2 b);

///////////////////////////////////////////////////////////////////////////////////////////////////

class ImageBuffer
{
private:
    std::string **buffer;
public:
    const int xres;
    const int yres;

    ImageBuffer(int n_xres, int n_yres, std::string fill = " ");

    void setPixel(int x, int y, std::string val);

    void setPixel(Vector2 point, std::string val);

    std::string getPixel(int x, int y);

    void drawHLine(int xpos, int ypos, int length, std::string val);

    void drawVLine(int xpos, int ypos, int length, std::string val);

    void drawRect(int x, int y, int width, int height);

    void drawFillRect(int xpos, int ypos, int width, int height, std::string fill);

    void putText(int xpos, int ypos, std::string string);

    ~ImageBuffer();
};

///////////////////////////////////////////////////////////////////////////////////////////////////

void drawImage(ImageBuffer &image);

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
