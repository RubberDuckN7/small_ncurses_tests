// Own defs
#include "timer.h"
#include "window.h"

// System stuff
#include <stdio.h>
#include <ncurses.h>
#include <chrono>
#include <ratio>
#include <thread>


int main(void)
{
  Timer timer;

  Window window;
  window.create();
  
  Rect titleBounds(0, 0, window.getWidth(), 3);
  Rect editorBounds(15, 3, window.getWidth()-15, window.getHeight()-4);
  Rect navigatorBounds(0, 3, 15, window.getHeight()-4);

  Window::SubWindow * title = window.getSubWindow(titleBounds);
  Window::SubWindow * editor = window.getSubWindow(editorBounds);
  Window::SubWindow * navigator = window.getSubWindow(navigatorBounds);

  window.set_border('.', '-');
  title->set_border('.', '-');
  editor->set_border('.', '-');
  navigator->set_border('.', '-');

  bool running = true;

  window.setOnKeyPressed([&running](int key) {
    if(key == VL_KEY_f)
      running = false;
  });

  window.setOnKeyReleased([](int key) {

  });
  init_color(COLOR_BLACK, 0, 0, 255);
  init_color(COLOR_RED, 255, 0, 0);
  start_color();
  
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  while(running)
  {
    window.clear();
    window.processInput();
    
    title->colorOn(1);
    title->write(1,1, "Moooooo!");
    
    title->colorOff(2);  

    std::string data = std::to_string(timer.getDeltaTime());
    window.write(0, window.getHeight()-1, data);
    
    window.move_cursor(1, 20);
    window.write_append("");
    title->move_cursor(0, 20);

    editor->write(1,1, "Editor!");
    navigator->write(1,1, "Navigator!");

    editor->move_cursor(5, 5);
    editor->write_append("L");   
    editor->write(7, 7, ""); 

    window.update();
    title->update(); 
    editor->update();
    navigator->update();

    editor->touch();
    navigator->touch();
    title->touch();

    // This needs to be sleeping at least this much, since
    // anything less, cause flickering. No swap chain :(
    this_thread::sleep_for(100ms);

    timer.tick();
  }

  title->release();
  window.release();
  printf("Ended.\n");
  return 0;
}