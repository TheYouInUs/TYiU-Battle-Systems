/*
 * Vector3f.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#include "Vector3f.h"
#include <math.h>

Vector3f::Vector3f() :
		x(0), y(0), z(0) {

}

Vector3f::Vector3f(float a, float b, float c) :
		x(a), y(b), z(c) {
}

Vector3f::~Vector3f() {
}

Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f Vector3f::operator -(Vector3f a) {
	return this->clone() -= a;
}

Vector3f Vector3f::operator -=(Vector3f a) {
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;
	return this;
}

Vector3f Vector3f::operator +(Vector3f a) {
	return this->clone() += a;
}

Vector3f Vector3f::operator +=(Vector3f a) {
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
	return this;
}

Vector3f Vector3f::operator *(float s) {
	return this->clone() *= s;
}

Vector3f Vector3f::operator *=(float s) {
	x *= s;
	y *= s;
	z *= s;
	return this;
}

bool Vector3f::operator ==(Vector3f a) {
	return a.x == x && a.y == y && a.z == z;
}

bool Vector3f::operator !=(Vector3f a) {
	return !(this == a);
}

Vector3f Vector3f::clone() {
	return Vector3f(x, y, z);
}

Vector3f Vector3f::normalize() {
	float mag = magnitude();
	if (mag != 0) {
		x /= mag;
		y /= mag;
		z /= mag;
	}
	return this;
}

float Vector3f::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3f::dotProduct(Vector3f u, Vector3f v) {
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

Vector3f Vector3f::crossProduct(Vector3f u, Vector3f v) {
	return Vector3f((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z),
			(u.x * v.y) - (u.y * v.x));
}
