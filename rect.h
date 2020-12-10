#pragma once

struct Rect
{
  int X; int Y; int Width; int Height;
  Rect() : X(0), Y(0), Width(0), Height(0) {}
  Rect(int startX, int startY, int width, int height) 
    : X(startX), Y(startY), Width(width), Height(height) {}
};