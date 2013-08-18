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
protected:
	// Load and unload methods
	virtual bool load(const char* fname) = 0;
	virtual void unload() = 0;
};

#endif /* RESOURCE_H_ */
