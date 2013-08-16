/*
 * ResourceManager.h
 *
 *  Created on: Aug 16, 2013
 *      Author: westin
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

class Resource;
#include <vector>

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

	template <typename Resource_T>
	Resource_T *find(const char *fileName);

	void destroy(Resource *res);
};

#endif /* RESOURCEMANAGER_H_ */
