#include <stdio.h>
#include <ncurses.h>
#include <chrono>
#include <ratio>
#include <thread>

// Mein key kodez
  #define VL_MLBUTTON 0
  #define VL_MRBUTTON 1
  #define VL_MMBUTTON 2

  #define VL_ACTION_PRESS 0
  #define VL_ACTION_MOVE 1
  #define VL_ACTION_RELEASE 2

  #define VL_KEY_SPACE 32
  #define VL_KEY_DEL 127
  #define VL_KEY_ENTER 13

  #define VL_KEY_A 65
  #define VL_KEY_B 66 
  #define VL_KEY_C 67
  #define VL_KEY_D 68
  #define VL_KEY_E 69
  #define VL_KEY_F 70
  #define VL_KEY_G 71
  #define VL_KEY_H 72
  #define VL_KEY_I 73
  #define VL_KEY_J 74
  #define VL_KEY_K 75
  #define VL_KEY_L 76
  #define VL_KEY_M 77
  #define VL_KEY_N 78
  #define VL_KEY_O 79
  #define VL_KEY_P 80
  #define VL_KEY_Q 81
  #define VL_KEY_R 82
  #define VL_KEY_S 83
  #define VL_KEY_T 84
  #define VL_KEY_U 85
  #define VL_KEY_V 86
  #define VL_KEY_W 87
  #define VL_KEY_X 88
  #define VL_KEY_Y 89
  #define VL_KEY_Z 90

  #define VL_KEY_a 97
  #define VL_KEY_b 98
  #define VL_KEY_c 99
  #define VL_KEY_d 100
  #define VL_KEY_e 101
  #define VL_KEY_f 102
  #define VL_KEY_g 103
  #define VL_KEY_h 104
  #define VL_KEY_i 105
  #define VL_KEY_j 106
  #define VL_KEY_k 107
  #define VL_KEY_l 108
  #define VL_KEY_m 109
  #define VL_KEY_n 110
  #define VL_KEY_o 111
  #define VL_KEY_p 112
  #define VL_KEY_q 113
  #define VL_KEY_r 114
  #define VL_KEY_s 115
  #define VL_KEY_t 116
  #define VL_KEY_u 117
  #define VL_KEY_v 118
  #define VL_KEY_w 119
  #define VL_KEY_x 120
  #define VL_KEY_y 121
  #define VL_KEY_z 122

/* Dafuqs of the year
  constexpr auto get_state = []()constexpr
  {
    auto state = constexpr_string(
      #include "text.txt" // R"in file"
    );
    
    return state;
  };
*/

// I don't even know why.....
#define WINDOW_CONTENT\
  WINDOW * mainWindow;
  
#define ABSTRACT(name)\
  virtual name = 0;
#define OVERRIDE(name) \
  virtual name
  
#define TIME std::chrono::system_clock::now();

// Wait for it... wait for ... it ...
#define CLOCK_F(x) \
  test_x()\
  {\
    Timer timer;\
    timer.start();\
    x();\
    timer.tick();\
    printf("Method finished with: %f\n", time.getDeltaTime());\
  }

// What the hell, let's just go all in with Shitty-Code-Production.
using namespace std;
using namespace chrono_literals;

class Timer
{
public:
  // Do I even need this?
  using seconds      = std::chrono::duration<double>;
  using milliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
  using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;

  Timer() {}

  long long getTotalTimeMilliSec();
  float getDeltaTime();
  void init();
  void tick();
  void endFrame();

private:
  std::chrono::system_clock::time_point currentTime;
  std::chrono::system_clock::time_point lastTime;
};

float Timer::getDeltaTime()
{
  std::chrono::duration<float, std::milli> dt = currentTime - lastTime;
  return dt.count();
}

void Timer::init()
{ 
  currentTime = TIME
  lastTime = TIME 
}

void Timer::tick()
{
  lastTime = currentTime;
  currentTime = TIME
}

class Clocking
{
public:
  Clocking() = default;
  ~Clocking() = default;
  void run();

private:

};

struct Rect
{
  int StartX; int StartY; int Width; int Height;
  Rect() : StartX(0), StartY(0), Width(0), Height(0) {}
  Rect(int startX, int startY, int width, int height) : StartX(startX), StartY(startY), Width(width), Height(height) {}
};

class WindowShell
{
public:
  virtual bool create(Rect rect) = 0;
  virtual void write(int x, int y, std::string msg) = 0;
  virtual void write_append(std::string msg) = 0;
  virtual void moveto(int x, int y) = 0;
  virtual void release() = 0;
protected:
  Rect bounds;
public:
  inline const Rect & getBounds() { return bounds; }
};

class VioletWindow : public WindowShell
{
public:
  class SubWindow : public WindowShell
  {
    public:
      virtual bool create(Rect rect);
      virtual void write(int x, int y, std::string msg);
      virtual void write_append(std::string msg);
      virtual void moveto(int x, int y);
      virtual void release();
      void refresh();
    private:
      WINDOW_CONTENT
  };
public:
  virtual bool create(Rect rect);
  virtual void write(int x, int y, std::string msg);
  virtual void write_append(std::string msg);
  virtual void moveto(int x, int y);
  virtual void release();
  SubWindow * getSubWindow(const Rect & rect);
private:
  WINDOW_CONTENT
public:
};

bool VioletWindow::SubWindow::create(Rect rect)
{
  mainWindow = newwin(rect.Height, rect.Width, rect.StartX, rect.StartY);
  box(mainWindow, 0, 0);
  return true;
}

void VioletWindow::SubWindow::write(int x, int y, std::string msg)
{
  mvwaddstr(mainWindow, y, x, msg.c_str());
}

void VioletWindow::SubWindow::write_append(std::string msg)
{
  waddstr(mainWindow, msg.c_str());
}

void VioletWindow::SubWindow::moveto(int x, int y)
{

}

void VioletWindow::SubWindow::release()
{
  delwin(mainWindow);
}

void VioletWindow::SubWindow::refresh()
{
  touchwin(mainWindow);
  wrefresh(mainWindow);
}

bool VioletWindow::create(Rect rect)
{
  mainWindow = initscr();
  
  // Doesn't print to screen a key, when pressed.
  noecho();
  cbreak();
  
  getmaxyx(mainWindow, bounds.Height, bounds.Height);
  
  if(rect.Width > bounds.Width || rect.Height > bounds.Height)
  {
    // No win :(
    endwin();
    return false;
  }
  
  nodelay(mainWindow, true);
  
  // Setup rest of the stuff here
  return true;
}

void VioletWindow::write(int x, int y, std::string msg)
{
  mvaddstr(y,  x, msg.c_str());
}

void VioletWindow::write_append(std::string msg)
{
  addstr(msg.c_str());
}

void VioletWindow::moveto(int x, int y)
{

}

void VioletWindow::release()
{
  endwin();
}

VioletWindow::SubWindow * VioletWindow::getSubWindow(const Rect & rect)
{
  SubWindow * subwindow = new SubWindow();
  subwindow->create(rect);
  return subwindow;
  //WINDOW * subWindow = newwin(x, y, width, height);
}

/*
/// TODO: Add auto subwindow handling (From rect), options: popup? exit action? switch action?
//        Add border drawing
class VioletWindow2
{
private:
  WINDOW_CONTENT
public:
  class SubWindow
  {
    WINDOW_CONTENT
    public:
      SubWindow(WINDOW * window, int height, int width) : 
        mainWindow(window) {}
      void release(); 
  };
  
public:
  VioletWindow2() : mainWindow(0), terminalWidth(0), terminalHeight(0) {}
  ~VioletWindow2() = default;
  
  bool startUp(int minBoundsWidth, int minBoundsHeight);
  void shutDown();
  SubWindow * getSubWindow(int x, int y, int width, int height);
  inline int getWidth() { return terminalWidth; }
  inline int getHeight() { return terminalHeight; }

public:
};

void VioletWindow2::SubWindow::release()
{
  delwin(mainWindow);
  delete this;
}

bool VioletWindow2::startUp(int minBoundsWidth, int minBoundsHeight)
{
  mainWindow = initscr();
  
  // Doesn't print to screen a key, when pressed.
  noecho();
  cbreak();
  
  
  getmaxyx(mainWindow, terminalHeight, terminalWidth);
  
  if(minBoundsWidth > terminalWidth || minBoundsHeight > terminalHeight)
  {
    // No win :(
    endwin();
    return false;
  }
  
  nodelay(mainWindow, true);
  
  // Setup rest of the stuff here
  return true;
}

void VioletWindow2::shutDown()
{
  endwin();
}

VioletWindow2::SubWindow * VioletWindow2::getSubWindow(int x, int y, int width, int height)
{
  SubWindow * subwindow = new SubWindow(newwin(x, y, width, height), width, height);
  return subwindow;
  //WINDOW * subWindow = newwin(x, y, width, height);
}*/

class Potatoe
{
public:
  Potatoe() : running(false) {}
  void create(int width, int height);
  void start();
  void shutDown();
  
private:
  void run();  
  void update(float dt);
  void draw();
  void processInput();
  
  
private:
  VioletWindow window;
  bool running;
};

void Potatoe::create(int width, int height)
{
  Rect rect(0, 0, 0, 0);
  window.create(rect);
  //printf("Creating potatoe...\n");
}

void Potatoe::start()
{
  //printf("Starting potatoe...\n");
  running = true;
  run();
}

void Potatoe::run()
{
  Rect titleBounds(0, 4, window.getBounds().Width, 3);

  VioletWindow::SubWindow * title = window.getSubWindow(titleBounds);

  //printf("Running potatoe...\n");
  Timer time;
  
  time.init();

  float totalTime = 0.0f;

  while(running)
  {
    // Do clock stuff
    float deltaTime = time.getDeltaTime();
    
    // Update
    update(deltaTime);
    
    this_thread::sleep_for(100ms);
    
    time.tick();
    
    
    window.write(0, 0, std::string("Delta time: ") + std::to_string(time.getDeltaTime()));
    window.write(0, 1, std::string("Heya: "));
    window.write_append(std::string("Mooo"));
    
    //mvprintw(0, 0, "Delta time: %f", time.getDeltaTime());
    refresh();

    title->write(0, 1, "Bugugugu");
    title->refresh();

    //std::string data = std::to_string(time.getDeltaTime());
    //addstr(data.c_str());
    //printf("Game Delta time: %f\n", time.getDeltaTime());
    //fflush(stdout);
    // Draw
    draw();
    
    totalTime += deltaTime;
    //if(totalTime > 2000.0f)
    if(getch() == VL_KEY_f)
    {
      running = false;
    }
  }

  title->release();
}

void Potatoe::update(float dt)
{
}

void Potatoe::draw()
{

}

void Potatoe::processInput()
{
  // So magically, do this:
  // onKeyPressed(key)
  // onKeyReleased(key)
  // from this:
  // nodelay(), if no keys were pressed, getch returns ERR.
  // key = getch()
}

void Potatoe::shutDown()
{
  window.release();
}

#include <string>
#include <vector>

int main()
{
  //Clocking clock;
  
  //clock.run();

  //return 0;

  Timer timer;
  // Set initial values.
  timer.tick();
  
  printf("Starting the game!... with ncurses... in like... forever...\n");
  //VioletWindow2 window;
  
  //addstr("Test");
  //refresh();
  
  std::vector<std::string> all;
  
  // Bounds first, then coordinates
  //WINDOW * sub = window.getSubWindow(2, window.getWidth(), 0, 0);
  
  //if(sub == NULL)
  //{
  //  addstr("NULL");
  //}
  
  // Is not written
  //mvwaddstr(sub, 0, 10, "Heya");
  
  //box(sub, 0, 0);
  
  // This one... why?
  //touchwin(sub);
  
  // This is needed to show update on screen.
  //wrefresh(sub);
  
  // 27
  /*for(int i = 0; i < 30; i++)
  {
    int ch = getch();
    
    std::string data = std::to_string(ch);
    all.push_back(data);
    move(i, 0);
    addstr(data.c_str());
    
  }*/
  
  //this_thread::sleep_for(5s);
  
  
  
  //for(int i = 0; i < all.size(); i++)
  //{
  //  printf("%s\n", all[i].c_str());
  //}
  
  //WINDOW * window = initscr();
  
  //int width;
  //int height;
  
  // Reversed, and measurement is in characters.
  //getmaxyx(window, height, width);
  
  //addstr("Test");
  //refresh();
  //getch();
  //endwin();
  
  
  
  // Starting
  Potatoe potatoe;
  potatoe.create(0, 0);

  potatoe.start();

  timer.tick();

  potatoe.shutDown();
  
  //printf("Width: %i, height: %i\n", window.getWidth(), window.getHeight());
  printf("Program ended.\n");
  return 0;
}

void stuff1S()
{
  this_thread::sleep_for(1s);
}

void stuff3S()
{
  this_thread::sleep_for(3s);
}

void Clocking::run()
{
  //CLOCK_F(stuff1S);
  //CLOCK_F(stuff3S);
}