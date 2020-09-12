#ifndef _MODEL_H_
#define _MODEL_H_
#include "object.h"
#include "texturemanager.h"
#include "objloader.h"

class Model: public Object
{
private:
	TextureManager* texman;
	std::vector<tinyobj::shape_t> shapes;
public:
	Model(TextureManager* texman);
	virtual void render();
	virtual float* getVertexes();
	virtual unsigned int getVertexCount();
	void load(std::string model);
};

#endif /* _MODEL_H_ */