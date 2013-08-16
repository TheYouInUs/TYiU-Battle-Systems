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
