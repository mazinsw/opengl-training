#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "object.h"
#include "player.h"
#include <list>

class SceneManager: public MoveAction
{
private:
	std::list<Object*> objects;
protected:
	
public:
	~SceneManager();
	virtual bool move(const Object& obj);
	void clear();
	void add(Object* object);
	void render();
};

#endif /* _SCENEMANAGER_H_ */