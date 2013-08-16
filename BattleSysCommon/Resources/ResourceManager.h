/*
 * ResourceManager.h
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Resource.h"
#include <vector>
#include <stdio.h>
#include <string.h>

class ResourceManager {
private:
	static ResourceManager *instance;

	std::vector<Resource*> resources;
	bool initialized;
public:
	static ResourceManager *get();

	ResourceManager();
	virtual ~ResourceManager();

	void initialize(int poolSize);
	void terminate();

	template<typename Resource_T>
	Resource_T *find(const char *fileName);

	void destroy(Resource *res);
};

template<typename Resource_T>
Resource_T *ResourceManager::find(const char *fileName) {
	// Check if the resource manager is initialized
	if (!initialized) {
		fprintf(stderr, "Resource manager not initialized!\n");
		return NULL;
	}

	// Is it already loaded?
	Key resourceKey = Resource::generateKey(fileName);
	for (register std::vector<Resource*>::iterator itr = resources.begin();
			itr != resources.end(); ++itr) {
		if (NULL != (*itr) && (*itr)->resourceKey == resourceKey
				&& strcmp(fileName, (*itr)->loadedFile)) {
			(*itr)->refCount++;
			return (Resource_T*) (*itr);
		}
	}

	//Not already loaded, create it

	// Can we load it?
	if (resources.size() >= resources.capacity()) {
		fprintf(stderr, "Resource manager is full!\n");
		return NULL;
	}

	// Load it
	Resource_T *resource = new Resource_T;
	Resource *resActual = (Resource*) resource;
	resActual->load(fileName);
	resActual->refCount = 1;
	resActual->loadedFile = fileName;
	resActual->resourceKey = resourceKey;
	resources.push_back(resActual);
	return resource;
}

#endif /* RESOURCEMANAGER_H_ */
