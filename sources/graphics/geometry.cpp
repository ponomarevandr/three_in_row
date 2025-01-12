#include "geometry.h"

#include <cmath>
#include <algorithm>


namespace Graphics {

int sign(int value) {
	if (value > 0)
		return 1;
	if (value == 0)
		return 0;
	return -1;
}


Point::Point(int x, int y): x(x), y(y) {}

Point& Point::operator+=(const Vector& vector) {
	x += vector.x;
	y += vector.y;
	return *this;
}

Point& Point::operator-=(const Vector& vector) {
	x -= vector.x;
	y -= vector.y;
	return *this;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}


Vector::Vector(int x, int y): x(x), y(y) {}

Vector& Vector::operator+=(const Vector& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector& Vector::operator-=(const Vector& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector Vector::operator-() const {
	return Vector(-x, -y);
}

Vector& Vector::operator*=(int multiplier) {
	x *= multiplier;
	y *= multiplier;
	return *this;
}

Vector& Vector::operator/=(int divisor) {
	x /= divisor;
	y /= divisor;
	return *this;
}

bool Vector::operator==(const Vector& other) const {
	return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector& other) const {
	return !(*this == other);
}

Vector Vector::direction() const {
	return Vector(sign(x), sign(y));
}

int Vector::manhattanLength() const {
	return std::abs(x) + std::abs(y);
}


Point operator+(const Point& point, const Vector& vector) {
	Point result = point;
	result += vector;
	return result;
}

Point operator-(const Point& point, const Vector& vector) {
	Point result = point;
	result -= vector;
	return result;
}

Vector operator-(const Point& end, const Point& beginning) {
	return Vector(end.x - beginning.x, end.y - beginning.y);
}

Vector operator+(const Vector& first, const Vector& second) {
	Vector result = first;
	result += second;
	return result;
}

Vector operator-(const Vector& first, const Vector& second) {
	Vector result = first;
	result -= second;
	return result;
}

Vector operator*(const Vector& vector, int multiplier) {
	Vector result = vector;
	result *= multiplier;
	return result;
}

Vector operator*(int multiplier, const Vector& vector) {
	Vector result = vector;
	result *= multiplier;
	return result;
}

Vector operator/(const Vector& vector, int divisor) {
	Vector result = vector;
	result /= divisor;
	return result;
}

int crossProduct(const Vector& first, const Vector& second) {
	return first.x * second.y - first.y * second.x;
}

int dotProduct(const Vector& first, const Vector& second) {
	return first.x * second.x + first.y * second.y;
}

const Vector RIGHT(1, 0);
const Vector UP(0, -1);
const Vector LEFT(-1, 0);
const Vector DOWN(0, 1);
const Vector NORTH_EAST(1, -1);
const Vector NORTH_WEST(-1, -1);
const Vector SOUTH_WEST(-1, 1);
const Vector SOUTH_EAST(1, 1);


Segment::Segment(const Point& first, const Point& second): first(first), second(second) {}


void Rectangle::sort(int& first, int& second) {
	if (first > second) {
		std::swap(first, second);
	}
}

Rectangle::Rectangle(const Point& top_left, const Point& bottom_right):
		top_left(top_left), bottom_right(bottom_right) {
	sort(this->top_left.x, this->bottom_right.x);
	sort(this->top_left.y, this->bottom_right.y);
}

Rectangle::Rectangle(const Point& top_left, int width, int height):
	Rectangle(top_left, top_left + Vector(width, height)) {}


int Rectangle::getWidth() const {
	return bottom_right.x - top_left.x;
}

int Rectangle::getHeight() const {
	return bottom_right.y - top_left.y;
}

Point Rectangle::getCenter() const {
	return top_left + (bottom_right - top_left) / 2;
}

bool Rectangle::isPointInside(const Point& point) const {
	return
		top_left.x <= point.x && point.x <= bottom_right.x &&
		top_left.y <= point.y && point.y <= bottom_right.y;
}

}