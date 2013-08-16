/*
 * Resource.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#include "Resource.h"
#include <string.h>

Resource::Resource() :
		refCount(0), resourceKey(0), loadedFile(NULL) {
}

Resource::~Resource() {
}

Key Resource::generateKey(const char* str) {
	Key generated = 0;
	unsigned int sLength = strlen(str);
	register unsigned int cIdx, bIdx;
	for (cIdx = 0, bIdx = 0; cIdx < sLength; cIdx++, bIdx++) {
		if (bIdx > sizeof(Key)) {
			bIdx = 0;
		}
		generated ^= (str[cIdx] << bIdx);
	}
	return generated;
}
