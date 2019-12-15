#include <iostream>
#include "../headers/graphics.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//ImageBuffer function
///////////////////////////////////////////////////////////////////////////////////////////////////

ImageBuffer::ImageBuffer(int n_xres, int n_yres, std::string fill): xres(n_xres), yres(n_yres)
{
    buffer = new std::string*[xres * yres];

    for(int i = 0; i < xres * yres; ++i)
    {
        buffer[i] = new std::string;
        *buffer[i] = fill;
    }
}

void ImageBuffer::setPixel(int x, int y, std::string val)
{
    if(x < 0 || x >= xres || y < 0 || y >= yres)
    {
        return;
    }

    *buffer[x + y * xres] = val;
}

void ImageBuffer::setPixel(Vector2 point, std::string val)
{
    setPixel(round(point.x), round(point.y), val);
}

std::string ImageBuffer::getPixel(int x, int y)
{
    return *buffer[x + y * xres];
}

void ImageBuffer::drawHLine(int xpos, int ypos, int length, std::string val)
{
    for(int i = xpos; i < xpos + length; ++i)
    {
        setPixel(i, ypos, val);
    }
}

void ImageBuffer::drawVLine(int xpos, int ypos, int length, std::string val)
{
    if(length <= 0)
    {
        return;
    }

    for(int i = ypos; i < ypos + length; ++i)
    {
        setPixel(xpos, i, val);
    }
}

void ImageBuffer::drawRect(int xpos, int ypos, int width, int height)
{
    if(width <= 2)
    {
        width = 2;
    }
    if(height <=  2)
    {
        height = 2;
    }

    setPixel(xpos, ypos, "\u2554");
    setPixel(xpos + width - 1, ypos, "\u2557");
    setPixel(xpos, ypos + height - 1, "\u255a");
    setPixel(xpos + width - 1, ypos + height - 1, "\u255d");

    drawHLine(xpos + 1, ypos, width - 2, "\u2550");
    drawHLine(xpos + 1, ypos + height - 1, width - 2, "\u2550");
    drawVLine(xpos, ypos + 1, height - 2, "\u2551");
    drawVLine(xpos + width - 1, ypos + 1, height - 2, "\u2551");
}

void ImageBuffer::drawFillRect(int xpos, int ypos, int width, int height, std::string fill)
{
    if(width < 1 || height < 1)
    {
        return;
    }
    for(int x = xpos; x < xpos + width; ++x)
    {
        for(int y = ypos; y < ypos + height; ++y)
        {
            setPixel(x, y, fill);
        }
    }
}

void ImageBuffer::putText(int xpos, int ypos, std::string string)
{
    for(size_t i = 0; i < string.length(); ++i)
    {
        std::string val;
        val.push_back(string.at(i));
        setPixel(xpos + i, ypos, val);
    }
}

ImageBuffer::~ImageBuffer()
{
    for(int i = 0; i < xres * yres; ++i)
    {
        delete buffer[i];
    }

    delete[] buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//Vector2 functions
///////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 operator+(Vector2 a, Vector2 b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(Vector2 a, Vector2 b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void drawImage(ImageBuffer &image)
{
    std::cout << "\e[1;1H";

    for(int y = 0; y < image.yres; ++y)
    {
        for(int x = 0; x < image.xres; ++x)
        {
            std::cout << image.getPixel(x, y);
        }
        std::cout << '\n';
    }
}
