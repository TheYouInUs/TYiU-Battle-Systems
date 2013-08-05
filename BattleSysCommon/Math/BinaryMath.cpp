/*
 * BinaryMath.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: lwestin
 */

#include "BinaryMath.h"

int get2Fold_i(int t) {
	int i = 1;
	while (i < t) {
		i <<= 1;
	}
	return i;
}

unsigned int get2Fold_ui(unsigned int t) {
	unsigned int i = 1;
	while (i < t) {
		i <<= 1;
	}
	return i;
}
