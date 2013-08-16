/*
 * ResourceManager.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#include "ResourceManager.h"
#include <string.h>
#include <stdio.h>
#include "Resource.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager() :
		initialized(false) {
}

ResourceManager::~ResourceManager() {
	if (this == instance) {
		instance = NULL;
	}
}

ResourceManager *ResourceManager::get() {
	if (NULL == instance) {
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::initialize(int iPoolSize) {
	if (!initialized) {
		resources = std::vector<Resource*>();
		resources.reserve(iPoolSize);
		initialized = true;
	}
}

void ResourceManager::terminate() {
	if (initialized) {
		for (std::vector<Resource*>::iterator itr = resources.begin();
				itr != resources.end(); ++itr) {
			(*itr)->unload();
			delete (*itr);
		}
	}
}

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

void ResourceManager::destroy(Resource *res) {
	res->refCount--;
	if (res->refCount <= 0) {
		// We need to delete it
		for (register std::vector<Resource*>::iterator itr = resources.begin();
				itr != resources.end(); ++itr) {
			if (NULL != (*itr) && (*itr)->resourceKey == res->resourceKey
					&& strcmp(res->loadedFile, (*itr)->loadedFile)) {
				resources.erase(itr);
				delete (*itr);
				return;
			}
		}
	}
}
