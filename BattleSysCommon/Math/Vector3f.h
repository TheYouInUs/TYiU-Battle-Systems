/*
 * Vector3f.h
 *
 *  Created on: Aug 8, 2013
 *      Author: lwestin
 */

#ifndef VECTOR3F_H_
#define VECTOR3F_H_

class Vector3f {
public:
	float x, y, z;
	Vector3f();
	Vector3f(float, float, float);
	virtual ~Vector3f();
};

#endif /* VECTOR3F_H_ */
