#pragma once

#include "rect.h"
#include "keys.h"

#include <string>
#include <stdio.h>
#include <ncurses.h>
#include <functional>

class Window
{
public:
  // Fix this shit later.
  // There is a good idea for uber mega template that is a total brainfuck.
  class SubWindow
  {
    public:
      SubWindow(WINDOW * window, Rect bounds) { this->window = window; this->bounds = bounds;  }

      inline void write(int x, int y, std::string msg) {  mvwaddstr(window, y,  x, msg.c_str());  }
      inline void write_append(std::string msg) {  waddstr(window, msg.c_str());  }
      inline void touch() {  touchwin(window);  }
      inline void move_cursor(int x, int y) {  wmove(window, y, x);  }
      inline void update() {  wrefresh(window);  }
      inline void clear() {  wclear(window);  }
      inline void colorOn(int pairIndex) {  wattron(window, COLOR_PAIR(pairIndex));  }
      inline void colorOff(int pairIndex) {  wattroff(window, COLOR_PAIR(pairIndex));  }
      inline void release() { delwin(window); }
      inline void set_border(char vertical, char horizontal) {  box(window, vertical, horizontal);  }
      inline void unset_border() {  box(window, ' ', ' ');  }
    private:
      WINDOW * window;
      Rect bounds;
    public:
      inline int getWidth() {  return bounds.Width;  }
      inline int getHeight() {  return bounds.Height;  }
      inline int getX() {  return bounds.X;  }
      inline int getY() {  return bounds.Y;  }
  };
  
  class Input
  {
    public:
      //void (*onKeyPressed)(int);
      //void (*onKeyReleased)(int);
      std::function<void(int)> onKeyPressed;  
      std::function<void(int)> onKeyReleased;      


      Input()
      {
        onKeyPressed = [](int key) {};
        onKeyReleased = [](int key) {};
      }
  };

public:
  Window() = default;
  ~Window() = default;

  bool create();
  inline SubWindow * getSubWindow(Rect viewport)
  {
    WINDOW * subInstance = newwin(viewport.Height, viewport.Width, viewport.Y, viewport.X);
    SubWindow * subwindow = new SubWindow(subInstance,viewport);
    return subwindow;
  }

  inline void write(int x, int y, std::string msg) {  mvaddstr(y,  x, msg.c_str());  }
  inline void write_append(std::string msg) {  addstr(msg.c_str());  }
  inline void move_cursor(int x, int y) {  move(y, x);  }
  inline void update() {  refresh();  }
  inline void clear() {  wclear(window);  }
  inline void colorOn(int pairIndex) {  attron(COLOR_PAIR(pairIndex));  }
  inline void colorOff(int pairIndex) {  attroff(COLOR_PAIR(pairIndex));  }
  inline void release() { endwin(); }
  void processInput();
  inline void set_border(char vertical, char horizontal) {  box(window, vertical, horizontal);  }
  inline void unset_border() {  box(window, ' ', ' ');  }

private:
  WINDOW * window;
  Input inputCallbacks;
  int width;
  int height;
public:
  inline void setOnKeyPressed(auto keyPressedCallback) {  inputCallbacks.onKeyPressed = keyPressedCallback;  }
  inline void setOnKeyReleased(auto keyReleasedCallback) {  inputCallbacks.onKeyReleased = keyReleasedCallback;  }
  inline int getWidth() {  return width;  }
  inline int getHeight() {  return height;  }
};