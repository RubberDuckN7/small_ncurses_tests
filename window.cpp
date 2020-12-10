#include "window.h"

bool Window::create()
{
  window = initscr();
  noecho();
  cbreak();

  if(window == nullptr)
  {
    endwin();
    return false;
  }

  getmaxyx(window, height, width);
  nodelay(window, true);

  return true;
}

void Window::processInput()
{
  int key = getch();
  if(key != ERR)
  {
    // Right now support only pressed.
    // TODO: Implement HashTable solution for combos!
    inputCallbacks.onKeyPressed(key);
  }
}