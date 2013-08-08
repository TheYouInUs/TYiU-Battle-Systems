/*
 * GLTexture.h
 *
 *  Created on: Jul 31, 2013
 *      Author: lwestin
 */

#ifndef GLTEXTURE_H_
#define GLTEXTURE_H_

#include <stdio.h>

#define TEXTURE_LOAD_DEBUGGING	(1)
#define TEXTURE_LOAD_SUCCESS	(0)
#define TEXTURE_LOAD_ERROR		(1)

typedef unsigned int texid_t;

class GLTexture {
private:
	texid_t textureID;
	void *rawData;
	unsigned int width;
	unsigned int height;
	unsigned int pixFMT;
public:
	GLTexture();
	virtual ~GLTexture();
	int loadFromPNG(FILE *fp);
	int loadFromFile(char *fname);
	void freeRawData();
	void freeTexture();

	void loadToVRAM();
	void bind();
};

#endif /* TEXTURE_H_ */
