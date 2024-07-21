#pragma once


namespace Graphics {

void screenInitialize();
void screenRefresh();
void screenFinalize();

int getScreenWidth();
int getScreenHeight();


enum Color {
	BLACK = 0,
	RED = 1,
	GREEN = 2,
	YELLOW = 3,
	BLUE = 4,
	MAGENTA = 5,
	CYAN = 6,
	WHITE = 7
};

class ColorPair {
private:
	int pair_index;

public:
	ColorPair(Color foreground_color, Color background_color);
	~ColorPair();
};

}