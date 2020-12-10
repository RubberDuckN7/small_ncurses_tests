editor: editor.o timer.o window.o
	g++ -std=c++1z -o editor editor.o window.o timer.o -lncurses
editor.o: editor.cpp timer.h window.h keys.h
	g++ -std=c++1z editor.cpp -c
window.o: window.cpp window.h keys.h rect.h
	g++ -std=c++1z window.cpp -c
timer.o: timer.cpp timer.h
	g++ -std=c++1z -c timer.cpp