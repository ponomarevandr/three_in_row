#include "screen.h"

#include <ncurses.h>


namespace Graphics {

void screenInitialize() {
	initscr();
	cbreak();
	noecho();
}

void screenFinalize() {
	endwin();
}

}