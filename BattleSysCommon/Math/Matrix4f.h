/*
 * Matrix4f.h
 *
 *  Created on: Aug 11, 2013
 *      Author: lwestin
 */

#ifndef MATRIX4F_H_
#define MATRIX4F_H_

#define MATIDX(a,b) (a + (b<<2))

class Matrix4f {
private:
	float matrix[16];
public:
	Matrix4f();
	virtual ~Matrix4f();

	inline float get(int row, int col);
	inline void set(int row, int col, float f);

	Matrix4f operator *(Matrix4f);
	Matrix4f operator *=(Matrix4f);

	Matrix4f operator *(float);
	Matrix4f operator *=(float);

	Matrix4f operator +(Matrix4f);
	Matrix4f operator +=(Matrix4f);

	Matrix4f operator -(Matrix4f);
	Matrix4f operator -=(Matrix4f);

	Matrix4f copy();
};

#endif /* MATRIX4F_H_ */
