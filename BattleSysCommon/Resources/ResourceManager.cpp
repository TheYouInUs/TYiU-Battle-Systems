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
		initialized(false), loadThread(), resourcesMutex(), loadResourceSignal() {
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

void *ResourceManager::runThread(void *mgrPtr) {
	ResourceManager *mgr = (ResourceManager*) mgrPtr;
	fprintf(stdout, "Resource manager starting...\n");
	while (mgr->initialized) {
		mgr->runIteration();
	}
	fprintf(stdout, "Resource manager ending...\n");
	return NULL;
}

void ResourceManager::runIteration() {
	pthread_mutex_lock(&loadQueueMutex);
	if (loadQueue.size() == 0) {
		pthread_cond_wait(&loadResourceSignal, &loadQueueMutex);
	}
	if (loadQueue.size() > 0) {
		Resource *res = loadQueue.front();
		loadQueue.pop_front();
		pthread_mutex_unlock(&loadQueueMutex);

		// Now load it, releasing the lock while we do.
		if (res != NULL && !res->isLoaded) {
			res->load(res->resourceFile);
		}
	} else {
		pthread_mutex_unlock(&loadQueueMutex);
	}
}

void ResourceManager::waitForLoad(Resource *res) {
	while (!res->isLoaded) {
		// TODO better:
		// 	-Timeout and then manual read?
		//	-Read manually in the current thread without the call to loadAsync.
		usleep(1000); //1 millisecond
	}
}

void ResourceManager::initialize(int iPoolSize) {
	if (!initialized) {
		resources = std::vector<Resource*>();
		resources.reserve(iPoolSize);

		//Threading
		pthread_mutex_init(&resourcesMutex, NULL);
		pthread_mutex_init(&loadQueueMutex, NULL);
		pthread_cond_init(&loadResourceSignal, NULL);

		initialized = true;

		pthread_create(&loadThread, NULL, ResourceManager::runThread, this);
	}
}

void ResourceManager::terminate() {
	if (initialized) {
		initialized = false;

		//Threading
		pthread_cond_broadcast(&loadResourceSignal);
		pthread_join(loadThread, NULL);
		pthread_cond_destroy(&loadResourceSignal);
		pthread_mutex_destroy(&loadQueueMutex);
		pthread_mutex_destroy(&resourcesMutex);

		for (std::vector<Resource*>::iterator itr = resources.begin();
				itr != resources.end(); ++itr) {
			if ((*itr)->isLoaded) {
				(*itr)->unload();
			}
			delete (*itr);
		}
	}
}

void ResourceManager::destroy(Resource *res) {
	res->refCount--;
	// #sanity check
	if (res->refCount < 0) {
		fprintf(stderr,
				"DEAR GOD NO.  Resource loaded from %s has a negative reference count.\n",
				res->resourceFile);
	}
	if (res->refCount == 0) {
		// We need to delete it
		for (register std::vector<Resource*>::iterator itr = resources.begin();
				itr != resources.end(); ++itr) {
			if (NULL != (*itr) && (*itr)->resourceKey == res->resourceKey
					&& strcmp(res->resourceFile, (*itr)->resourceFile)) {
				pthread_mutex_lock(&resourcesMutex);
				resources.erase(itr);
				pthread_mutex_unlock(&resourcesMutex);

				// Aaaannnndddd.... check the load queue, just in case someone is stupid
				for (register std::deque<Resource*>::iterator litr =
						loadQueue.begin(); litr != loadQueue.end(); ++litr) {
					if (NULL != (*itr)
							&& (*itr)->resourceKey == res->resourceKey
							&& strcmp(res->resourceFile,
									(*itr)->resourceFile)) {
						pthread_mutex_lock(&loadQueueMutex);
						loadQueue.erase(litr);
						pthread_mutex_unlock(&loadQueueMutex);
					}
				}

				// Now we can delete and destroy with confidence!
				delete (*itr);
				return;
			}
		}
	}
}
