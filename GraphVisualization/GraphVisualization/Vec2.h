#pragma once

class Vec2 {
public:
	Vec2();
	Vec2(double, double);
	~Vec2();

	Vec2 operator+(const Vec2 &);
	Vec2 operator-(const Vec2 &);
	Vec2& operator+=(const Vec2 &);
	Vec2& operator-=(const Vec2 &);
	double operator*(const Vec2 &);
	Vec2 operator*(const double &);
	Vec2 operator/(const double &);
	double len();

public:
	double x, y;
};
