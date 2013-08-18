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
#include <deque>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

class ResourceManager {
private:
	static ResourceManager *instance;

	// Index of the first unloaded resource
	std::vector<Resource*> resources;
	std::deque<Resource*> loadQueue;

	bool initialized;

	pthread_t loadThread;
	pthread_mutex_t resourcesMutex;
	pthread_cond_t loadResourceSignal;
	pthread_mutex_t loadQueueMutex;

	static void* runThread(void *mgr);
	void runIteration();
	void destroyInternal();
public:
	static ResourceManager *get();

	ResourceManager();
	virtual ~ResourceManager();

	void initialize(int poolSize);
	void terminate();

	template<typename Resource_T>
	Resource_T *loadAsync(const char *fileName);

	template<typename Resource_T>
	Resource_T *loadSync(const char *fileName);

	void waitForLoad(Resource *res);

	void destroy(Resource *res);
};

template<typename Resource_T>
Resource_T *ResourceManager::loadAsync(const char *fileName) {
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
				&& strcmp(fileName, (*itr)->resourceFile)) {
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
	resActual->refCount = 1;
	resActual->resourceFile = fileName;
	resActual->resourceKey = resourceKey;
	pthread_mutex_lock(&resourcesMutex);
	resources.push_back(resource);
	pthread_mutex_unlock(&resourcesMutex);

	pthread_mutex_lock(&loadQueueMutex);
	pthread_cond_signal(&loadResourceSignal);
	loadQueue.push_back(resource);
	pthread_mutex_unlock(&loadQueueMutex);
	return resource;
}

template<typename Resource_T>
Resource_T *ResourceManager::loadSync(const char *fileName) {
	Resource_T *res = loadAsync<Resource_T>(fileName);
	if (res != NULL) {
		waitForLoad(res);
		return res;
	}
	return res;
}
#endif /* RESOURCEMANAGER_H_ */
