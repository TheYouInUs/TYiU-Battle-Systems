/*
 * TYIUMath.h
 *
 *  Created on: Jul 31, 2013
 *      Author: lwestin
 */

#ifndef TYIUMATH_H_
#define TYIUMATH_H_

#include <stdint.h>

template <class T>
T get2Fold(T t);

void setFlag(uint8_t *buffer, unsigned int flag, bool val);
bool getFlag(uint8_t *buffer, unsigned int flag);

// Inline Functions
inline void setFlag(uint8_t *buffer, unsigned int flag, bool val) {
	buffer[flag >> 3] |= (val ? 1 : 0) << (flag & 0b111);
}

inline bool getFlag(uint8_t *buffer, unsigned int flag) {
	return (buffer[flag >> 3] >> (flag & 0b111)) & 1;
}

#endif /* TYIUMATH_H_ */
