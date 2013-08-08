/*
 * Vector2f.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#include "Vector2f.h"
#include <math.h>

Vector2f::Vector2f() :
		x(0), y(0) {
}

Vector2f::Vector2f(float s, float t) :
		x(s), y(t) {
}

Vector2f::~Vector2f() {
}

Vector2f Vector2f::operator -(Vector2f a) {
	return this->clone() -= a;
}

Vector2f Vector2f::operator -=(Vector2f a) {
	this->x -= a.x;
	this->y -= a.y;
	return this;
}

Vector2f Vector2f::operator +(Vector2f a) {
	return this->clone() += a;
}

Vector2f Vector2f::operator +=(Vector2f a) {
	this->x += a.x;
	this->y += a.y;
	return this;
}

Vector2f Vector2f::operator *(float s) {
	return this->clone() *= s;
}

Vector2f Vector2f::operator *=(float s) {
	x *= s;
	y *= s;
	return this;
}

bool Vector2f::operator ==(Vector2f a) {
	return a.x == x && a.y == y;
}

bool Vector2f::operator !=(Vector2f a) {
	return !(this == a);
}

Vector2f Vector2f::clone() {
	return Vector2f(x, y);
}

Vector2f Vector2f::normalize() {
	float mag = magnitude();
	if (mag != 0) {
		x /= mag;
		y /= mag;
	}
	return this;
}

float Vector2f::magnitude() {
	return sqrt((x * x) + (y * y));
}

float Vector2f::dotProduct(Vector2f u, Vector2f v) {
	return (u.x * v.x) + (u.y * v.y);
}
