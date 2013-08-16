/*
 * Matrix4f.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: lwestin
 */

#include "Matrix4f.h"
#include <string.h>

Matrix4f::Matrix4f() {
	int r, c;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			set(r, c, (r == c ? 1.0 : 0.0));
		}
	}
}

Matrix4f::~Matrix4f() {
}

float Matrix4f::get(int row, int col) {
	return matrix[MATIDX(row,col)];
}

void Matrix4f::set(int row, int col, float f) {
	matrix[MATIDX(row,col)] = f;
}

Matrix4f Matrix4f::copy() {
	Matrix4f copy;
	memcpy(copy.matrix, matrix, 16 * sizeof(float));
	return copy;
}

Matrix4f Matrix4f::operator *=(Matrix4f a) {
	float data[16];
	int r, c, i;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			data[MATIDX(r,c)] = 0;
			for (i = 0; i < 4; i++) {
				data[MATIDX(r,c)] += get(r, i) * a.get(i, c);
			}
		}
	}
	memcpy(matrix, data, 16 * sizeof(float));
	return *this;
}

Matrix4f Matrix4f::operator *(Matrix4f a) {
	Matrix4f result;
	int r, c, i;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			result.matrix[MATIDX(r,c)] = 0;
			for (i = 0; i < 4; i++) {
				result.matrix[MATIDX(r,c)] += get(r, i) * a.get(i, c);
			}
		}
	}
	return result;
}

Matrix4f Matrix4f::operator *=(float f) {
	int r, c;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			matrix[MATIDX(r,c)] *= f;
		}
	}
	return *this;
}

Matrix4f Matrix4f::operator *(float f) {
	return copy() *= f;
}

Matrix4f Matrix4f::operator +=(Matrix4f f) {
	int r, c;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			matrix[MATIDX(r,c)] += f.get(r, c);
		}
	}
	return *this;
}

Matrix4f Matrix4f::operator -=(Matrix4f f) {
	int r, c;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			matrix[MATIDX(r,c)] -= f.get(r, c);
		}
	}
	return *this;
}

Matrix4f Matrix4f::operator -(Matrix4f f) {
	return copy() -= f;
}

Matrix4f Matrix4f::operator +(Matrix4f f) {
	return copy() += f;
}
