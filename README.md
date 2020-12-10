# README #

// for home, -lncurses seems to work only at the end
g++ -lncurses -std=c++1z main.cpp -o main -fgnu-tm

g++  -std=c++1z main.cpp -o main -lncurses

g++ -o main main.cpp -I/usr/include /usr/lib/arm-linux-gnueabihf/libcurses.so

For some reason, if GCC cannot find its own lib, add to variable:
export LD_LIBRARY_PATH=/app/vbuild/SLED11-x86_64/gcc/7.3.0/lib64/

Useful link for input:
http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html

Makefile:
test: test.o
	g++ -std=c++1z -lncurses -o test test.o

test.o: test.cpp
	g++ -std=c++1z test.cpp -c
	
test cpp
#include <stdio.h>
#include <ncurses.h>
#include <chrono>
#include <ratio>
#include <thread>

using namespace std;
using namespace chrono_literals;

using seconds      = std::chrono::duration<double>;
using milliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;

int main(void)
{
  initscr();

  // wait 1 sec
  this_thread::sleep_for(1s);

  endwin();
  printf("Ended.\n");
  return 0;
}
	
Example:
mayapp: main.o 2.0 3.0
	gcc -o myapp main.o 2.o 3.o
main.o: main.c a.h
	gcc -c main.c
2.o: 2.c a.h b.h
	gcc -c 2.c
3.o: 3.c b.h c.h
	gcc -c 3.c
	
### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact