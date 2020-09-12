#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "vertex.h"

class Object
{
protected:
	float *vq;
	int vq_count;
	void refresh();
public:
	Object();
	~Object();
	void scale(float x, float y, float z);
	void translate(float x, float y, float z);
	virtual void render() = 0;
	virtual bool collision(const Object& obj);
	virtual float* getVertexes() = 0;
	virtual unsigned int getVertexCount() = 0;
};

#endif /* _OBJECT_H_ */