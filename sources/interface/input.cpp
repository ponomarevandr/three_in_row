#include "input.h"

#include <ncurses.h>


namespace Interface {

int getKey() {
	return getch();
}

}