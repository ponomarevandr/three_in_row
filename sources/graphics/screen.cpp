#include "screen.h"

#include <ncurses.h>

#include <cmath>
#include <clocale>


namespace Graphics {

void initializeColorPairs() {
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 800, 0);
	init_color(COLOR_YELLOW, 1000, 1000, 0);
	init_color(COLOR_BLUE, 0, 0, 1000);
	init_color(COLOR_MAGENTA, 1000, 0, 1000);
	init_color(COLOR_CYAN, 0, 1000, 1000);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(Color::GREY, 920, 920, 920);
	init_color(Color::YELLOW_DARK, 920, 920, 0);
	init_color(Color::UNUSED_10, 0, 0, 0);
	init_color(Color::UNUSED_11, 0, 0, 0);
	init_color(Color::UNUSED_12, 0, 0, 0);
	init_color(Color::UNUSED_13, 0, 0, 0);
	init_color(Color::UNUSED_14, 0, 0, 0);
	init_color(Color::UNUSED_15, 0, 0, 0);
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; ++j) {
			init_pair(i * 16 + j, i, j);
		}
	}
}

int screen_width;
int screen_height;

void screenInitialize(float getch_rate) {
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	keypad(stdscr, true);
	noecho();
	timeout(std::lround(1000.0f / getch_rate));
	start_color();
	initializeColorPairs();
	curs_set(0);
	getmaxyx(stdscr, screen_height, screen_width);
}

void screenRefresh() {
	refresh();
}

void screenFinalize() {
	endwin();
}

int getScreenWidth() {
	return screen_width;
}

int getScreenHeight() {
	return screen_height;
}


ColorPair::ColorPair(Color foreground_color, Color background_color):
		pair_index(foreground_color * 16 + background_color) {
	attron(COLOR_PAIR(pair_index));
}

ColorPair::~ColorPair() {
	attroff(COLOR_PAIR(pair_index));
}


}