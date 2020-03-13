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

	/*
	Vector2D(double angle, double length, int i) {
		this->x = cos(angle) * length;
		this->y = sin(angle) * length;
	}
	*/

	/*
	double getAngle(Vector2D& vector) {
		double y = vector.normalize().y;
		double x = vector.normalize().x;
		double angle = asin(y / x);
		return angle;
	}

	void gravity(float dt, Vector2D* result) {
		float arg1 = getAngle(*this);
		float arg2 = 2.0 * M_PI;
		float angle = fmod(arg1, arg2);
		if (angle > 3.0 * M_PI / 4.0) {
			result = new Vector2D(cos(angle*(1 - 0.9*dt))*this->x, sin(angle*(1 - 0.9*dt))*this->y);
		} else {
			result = new Vector2D(cos(angle*(1 + 0.1*dt))*this->x, sin(angle*(1 + 0.1*dt))*this->y);
		}
	}
	*/


	Vector2D normalize() {
		return Vector2D(x / length(), y / length());
	}

	Vector2D() {
		this->x = 0;
		this->y = 0;
	}
};