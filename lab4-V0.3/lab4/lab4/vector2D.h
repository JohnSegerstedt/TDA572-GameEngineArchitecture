#pragma once


#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


class Vector2D {
public:
	double x;
	double y;

	Vector2D operator+(const Vector2D& rhs) {
		return Vector2D(x + rhs.x, y + rhs.y);
	}

	Vector2D operator-(const Vector2D& rhs) {
		return Vector2D(x - rhs.x, y - rhs.y);
	}

	Vector2D operator*(const Vector2D& rhs) {
		return Vector2D(x * rhs.x, y * rhs.y);
	}

	Vector2D operator/(const double& rhs) {
		return Vector2D(x / rhs, y / rhs);
	}

	Vector2D operator*(const double& rhs) {
		return Vector2D(x * rhs, y * rhs);
	}

	double dotProduct(const Vector2D& rhs) {
		return x * rhs.x + y * rhs.y;
	}

	double length() {
		return sqrt(x * x + y * y);
	}

	Vector2D(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double getAngle(const Vector2D& vector) {
		return asin(vector.y / vector.x);
	}

	Vector2D closestAxis() {
		float arg1 = getAngle(*this);
		float arg2 = 2.0 * M_PI;
		float angle = fmod(arg1, arg2);
		if (angle > M_PI / 4.0 && angle < 3.0 * M_PI / 4.0
			|| angle > 5.0 * M_PI / 4.0 && angle < 7.0 * M_PI / 4.0)
			return Vector2D(0, y);
		else return Vector2D(x, 0);
	}


	Vector2D normalize() {
		return Vector2D(x / length(), y / length());
	}

	Vector2D() {
		this->x = 0;
		this->y = 0;
	}
};