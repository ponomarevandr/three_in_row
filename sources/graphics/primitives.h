#pragma once

#include "graphics/geometry.h"
#include "graphics/screen.h"

#include <vector>
#include <string>


namespace Graphics {

void moveCursor(const Point&);


void drawString(const std::wstring& string, const Point& start, Color foreground_color,
	Color background_color);

void drawStringAtCenter(const std::wstring& string, const Rectangle& rectangle,
	Color foreground_color, Color background_color);

void drawSymbol(wchar_t symbol, const Point& point, Color foreground_color,
	Color background_color);


void drawSegment(const Segment& segment, Color foreground_color, Color background_color);

void drawCorner(const Point& point, const Vector& first, const Vector& second,
	Color foreground_color, Color background_color);

void drawLine(const std::vector<Point>& points, Color foreground_color, Color background_color,
	bool is_closed = false);

void drawBox(const Rectangle& rectangle, Color foreground_color, Color background_color);


void fillRectangle(const Rectangle& rectangle, Color color);

}