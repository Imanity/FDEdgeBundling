#include "Vec2.h"

#include <cmath>

Vec2::Vec2() {
}

Vec2::Vec2(double x_, double y_) {
	x = x_;
	y = y_;
}

Vec2::~Vec2() {
}

Vec2 Vec2::operator+(const Vec2 &v) {
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2 &v) {
	return Vec2(x - v.x, y - v.y);
}

Vec2& Vec2::operator+=(const Vec2 &v) {
	*this = *this + v;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2 &v) {
	*this = *this - v;
	return *this;
}

double Vec2::operator*(const Vec2 &v) {
	return x * v.x + y * v.y;
}

Vec2 Vec2::operator*(const double &v) {
	return Vec2(x * v, y * v);
}

Vec2 Vec2::operator/(const double &v) {
	return Vec2(x / v, y / v);
}

double Vec2::len() {
	return sqrt(x * x + y * y);
}
