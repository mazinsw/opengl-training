#include "scenemanager.h"

SceneManager::~SceneManager()
{
	std::list<Object*>::iterator it;
	
	for(it = objects.begin(); it != objects.end(); it++)
		delete *it;
}

bool SceneManager::move(const Object& obj)
{
	Object * o;
	std::list<Object*>::iterator it;
	
	for(it = objects.begin(); it != objects.end(); it++)
	{
		o = *it;
		if(o->collision(obj))
			return false;
	}
	return true;
}

void SceneManager::add(Object* object)
{
	objects.push_back(object);
}

void SceneManager::render()
{
	Object * obj;
	std::list<Object*>::iterator it;
	
	for(it = objects.begin(); it != objects.end(); it++)
	{
		obj = *it;
		obj->render();
	}
}

void SceneManager::clear()
{
	std::list<Object*>::iterator it;
	
	for(it = objects.begin(); it != objects.end(); it++)
		delete *it;
	objects.clear();
}

