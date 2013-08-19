/*
 * Resource.h
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

class ResourceManager;

typedef unsigned int Key;

class Resource {
	friend class ResourceManager;
private:
	int refCount;
	Key resourceKey;
	const char* resourceFile;
	bool isLoaded;
	static Key generateKey(const char* str);
public:
	Resource();
	virtual ~Resource();

	bool isResourceLoaded();

	const bool load(const char* fname);
	const void unload();
protected:
	// Load and unload methods
	virtual bool loadInternal(const char* fname) = 0;
	virtual void unloadInternal() = 0;
};

#endif /* RESOURCE_H_ */
