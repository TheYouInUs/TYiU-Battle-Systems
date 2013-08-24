/*
 * Vector2f.h
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#ifndef VECTOR2F_H_
#define VECTOR2F_H_

class Vector2f {
public:
	float x, y;
	Vector2f();
	Vector2f(float, float);
	virtual ~Vector2f();

	Vector2f normalize();
	float magnitude();
	Vector2f clone();

	inline Vector2f operator +(Vector2f);
	inline Vector2f operator +=(Vector2f);

	inline Vector2f operator -(Vector2f);
	inline Vector2f operator -=(Vector2f);

	inline Vector2f operator *(float);
	inline Vector2f operator *=(float);

	inline bool operator ==(Vector2f);
	inline bool operator !=(Vector2f);

	static float dotProduct(Vector2f, Vector2f);

	inline void set(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

#endif /* VECTOR2F_H_ */
