/*
 * Resource.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#include "Resource.h"
#include <string.h>
#include <stdio.h>

Resource::Resource() :
		refCount(0), resourceKey(0), resourceFile(NULL), isLoaded(false) {
}

Resource::~Resource() {
	unload();
}

bool Resource::isResourceLoaded() {
	return isLoaded;
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

const bool Resource::load(const char *fname) {
	if (isLoaded) {
		fprintf(stderr, "%s is already loaded!\n", fname);
		return false;
	}
	bool temp = loadInternal(fname);
	if (!temp) {
		return false;
	}
	isLoaded = true;
	return true;
}

const void Resource::unload() {
	if (!isLoaded) {
		unloadInternal();
		isLoaded = false;
	}
}
