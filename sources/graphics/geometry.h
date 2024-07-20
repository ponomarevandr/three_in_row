#pragma once


namespace Graphics {

int sign(int);

struct Point;
struct Vector;

struct Point {
	int x = 0;
	int y = 0;
	Point() = default;
	Point(int x, int y);
	Point& operator+=(const Vector&);
	Point& operator-=(const Vector&);
	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
};

struct Vector {
	int x = 0;
	int y = 0;
	Vector() = default;
	Vector(int x, int y);
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector operator-() const;
	Vector& operator*=(int multiplier);
	Vector& operator/=(int divisor);
	bool operator==(const Vector&) const;
	bool operator!=(const Vector&) const;
	Vector direction() const;
	int manhattanLength() const;
};

Point operator+(const Point&, const Vector&);
Point operator-(const Point&, const Vector&);
Vector operator-(const Point&, const Point&);
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(const Vector&, int multiplier);
Vector operator*(int multiplier, const Vector&);
Vector operator/(const Vector&, int divisor);
int crossProduct(const Vector&, const Vector&);
int dotProduct(const Vector&, const Vector&);

extern const Vector RIGHT;
extern const Vector UP;
extern const Vector LEFT;
extern const Vector DOWN;


struct Segment {
	Point first;
	Point second;
	Segment() = default;
	Segment(const Point& first, const Point& second);
};

struct Rectangle {
	Point top_left;
	Point bottom_right;
	static void sort(int&, int&);
	Rectangle() = default;
	Rectangle(const Point& top_left, const Point& bottom_right);
	Rectangle(const Point& top_left, int width, int height);
	int getWidth() const;
	int getHeight() const;
	Point getCenter() const;
};

}