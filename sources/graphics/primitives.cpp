#include "primitives.h"

#include <ncurses.h>

#include <algorithm>

#include "debug/output.h"


namespace Graphics {

void moveCursor(const Point& point) {
	move(point.y, point.x);
}

void drawString(const std::wstring& string, const Point& start, Color foreground_color,
		Color background_color) {
	moveCursor(start);
	ColorPair colors(foreground_color, background_color);
	addwstr(string.c_str());
}

void drawStringAtCenter(const std::wstring& string, const Rectangle& rectangle,
		Color foreground_color, Color background_color) {
	Point start = rectangle.getCenter();
	start.x -= (string.size() - 1) / 2;
	drawString(string, start, foreground_color, background_color);
}

void drawSymbol(wchar_t symbol, const Point& point, Color foreground_color,
		Color background_color) {
	std::wstring string(1, symbol);
	drawString(string, point, foreground_color, background_color);
}


void drawSegment(const Segment& segment, Color foreground_color, Color background_color) {
	Vector direction = (segment.second - segment.first).direction();
	int length = (segment.second - segment.first).manhattanLength() + 1;
	ColorPair colors(foreground_color, background_color);
	if (direction == RIGHT)
		mvhline(segment.first.y, segment.first.x, 0, length);
	if (direction == LEFT)
		mvhline(segment.second.y, segment.second.x, 0, length);
	if (direction == DOWN)
		mvvline(segment.first.y, segment.first.x, 0, length);
	if (direction == UP)
		mvvline(segment.second.y, segment.second.x, 0, length);
}

void drawCorner(const Point& point, const Vector& first, const Vector& second,
		Color foreground_color, Color background_color) {
	Vector first_direction = first.direction();
	Vector second_direction = second.direction();
	if (first_direction.manhattanLength() != 1 || second_direction.manhattanLength() != 1)
		return;
	if (crossProduct(first_direction, second_direction) == 0)
		return;
	if (crossProduct(first_direction, second_direction) > 0)
		std::swap(first_direction, second_direction);
	moveCursor(point);
	ColorPair colors(foreground_color, background_color);
	if (first_direction == RIGHT)
		addch(ACS_LLCORNER);
	if (first_direction == UP)
		addch(ACS_LRCORNER);
	if (first_direction == LEFT)
		addch(ACS_URCORNER);
	if (first_direction == DOWN)
		addch(ACS_ULCORNER);
}

void drawLine(const std::vector<Point>& points, Color foreground_color, Color background_color,
		bool is_closed) {
	for (size_t i = 0; i + 1 < points.size(); ++i) {
		drawSegment(Segment(points[i], points[i + 1]), foreground_color, background_color);
	}
	if (is_closed)
		drawSegment(Segment(points.back(), points[0]), foreground_color, background_color);
	for (size_t i = 1; i + 1 < points.size(); ++i) {
		drawCorner(points[i], points[i - 1] - points[i], points[i + 1] - points[i],
			foreground_color, background_color);
	}
	if (is_closed) {
		drawCorner(points[0], points.back() - points[0], points[1] - points[0],
			foreground_color, background_color);
		drawCorner(points.back(), points[points.size() - 2] - points.back(),
			points[0] - points.back(), foreground_color, background_color);
	}
}

void drawBox(const Rectangle& rectangle, Color foreground_color, Color background_color) {
	std::vector<Point> points(4);
	points[0] = points[1] = rectangle.top_left;
	points[2] = points[3] = rectangle.bottom_right;
	points[1].y = rectangle.bottom_right.y;
	points[3].y = rectangle.top_left.y;
	drawLine(points, foreground_color, background_color, true);
}


void fillRectangle(const Rectangle& rectangle, Color color) {
	std::wstring string(rectangle.getWidth() + 1, L' ');
	Point start = rectangle.top_left;
	for (int i = 0; i <= rectangle.getHeight(); ++i) {
		drawString(string, start, color, color);
		++start.y;
	}
}

void fillScreen(Color color) {
	Rectangle rectangle(Point(0, 0), getScreenWidth() - 1, getScreenHeight() - 1);
	fillRectangle(rectangle, color);
}

}