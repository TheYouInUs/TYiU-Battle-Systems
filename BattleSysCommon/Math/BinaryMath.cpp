/*
 * BinaryMath.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: lwestin
 */

#include "BinaryMath.h"

template <class T>
T get2Fold(T t) {
	T i = 1;
	while (i < t) {
		i <<= 1;
	}
	return i;
}
